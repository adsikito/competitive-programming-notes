# -*- coding: utf-8 -*-
"""学习工程笔记 lint —— 把《交付前自检清单》机器化。

用法（PowerShell 中执行）：
    python lint_notes.py                      # 扫描 学习工程\\笔记\\ 下全部 md
    python lint_notes.py 笔记\\二分.md -v      # 单文件，输出全部条目
    python lint_notes.py -o 报告.txt           # 报告写入文件（推荐：控制台中文可能乱码）

退出码：无 FAIL = 0，有 FAIL = 1（可作门禁）。

检查项编号：
    通用  C01 frontmatter 五项  C02 emoji 合规  C03 标题不跳级  C04 表格 ≤6 列
          C05 callout 规范      C06 单块单主标签  C07 双链口径（已解禁）  C08 尾部两节
          C09 代码块语言与长度  C10 mermaid 数量与文字版  C11 禁用措辞  C12 自检清单节
    讲解  L01 N 对 N 对账       L02 六段齐全      L03 预备概念节  L04 冲突登记节
          L05 假设与缺口登记    L06 易错总表节    L07 性质表      L08 设计动机
          L09 前置概念清单节    L10 编译验证记录
    复习  R01 P0/P1/P2 标注     R02 全篇 ≤600 行（仅 v1.1/v2.0 旧分支；v2.1 已废此限）
          R03 必备节            R04 文本树 ≥ mermaid
          v2.1 分支（review_v2_1）：六步详略对照体——R05 P0 卡识别信号 /
          R06 边界数据集折叠 / R07 最后复习日期 / R08 六步标记；无行数上限
"""
import argparse
import os
import re
import sys
from datetime import datetime

EMOJI_RANGES = [(0x1F000, 0x1FAFF), (0x2600, 0x27BF), (0x2B00, 0x2BFF), (0x25A0, 0x25FF)]
VS16 = 0xFE0F
REVIEW_ALLOWED = {0x274C, 0x2705, 0x2B50, 0x26A0}
CALLOUT_OK = {"note", "tip", "important", "warning", "caution", "example"}
HEAD_KEYS = ["tags", "优先级", "掌握状态", "来源", "生成日期"]
BAN_WORDS = ["显然", "易得", "（略）", "(略)"]
REVIEW_SECTIONS = ["知识框架总览", "待补知识点清单", "口诀集", "自测清单", "错题登记"]
SEG_MARKS = "①②③④⑤⑥"

PASS, FAIL, WARN = "PASS", "FAIL", "WARN"


class Note:
    def __init__(self, path):
        self.path = path
        self.name = os.path.basename(path)
        with open(path, encoding="utf-8") as f:
            self.raw = f.read()
        self.lines = self.raw.split("\n")
        self.n = len(self.lines)
        self.results = []
        self._mark_code()
        self.kind = self._kind()
        labels = {"lecture_v2": "讲解笔记(v2.5)", "lecture_v3": "讲解笔记(v3.0)",
                  "review_v1": "复习回顾版(v1.1)", "review_v2": "复习回顾版(v2.0)",
                  "review_v2_1": "复习回顾版(v2.1)",
                  "unknown": "未知类型"}
        self.kind_label = labels[self.kind]

    # ---------- 基础 ----------
    def add(self, code, status, msg, line=None):
        self.results.append((code, status, msg, line))

    def _mark_code(self):
        self.in_code = [False] * self.n
        self.fences = []
        open_at = None
        lang = ""
        for i, ln in enumerate(self.lines):
            if ln.lstrip().startswith("```"):
                self.in_code[i] = True
                if open_at is None:
                    open_at = i
                    lang = ln.lstrip()[3:].strip()
                else:
                    self.fences.append((lang, open_at, i))
                    open_at = None
            elif open_at is not None:
                self.in_code[i] = True
        self.unclosed = open_at is not None

    def frontmatter(self):
        if not self.lines or self.lines[0].strip() != "---":
            return None
        out = {}
        for ln in self.lines[1:]:
            if ln.strip() == "---":
                return out
            if ":" in ln:
                k, _, v = ln.partition(":")
                out[k.strip()] = v.strip()
        return None

    def _kind(self):
        fm = self.frontmatter()
        if fm and "复习回顾" in fm.get("tags", ""):
            if "问题日志" in self.raw or "最后复习日期" in self.raw:
                return "review_v2_1"
            if "框架卡片" in self.raw:
                return "review_v2"
            return "review_v1"
        if any(re.match(r"^###\s*K-\d+", ln) for ln in self.lines):
            return "lecture_v2"
        if any(re.match(r"^###\s*\d+\.\s*\S", ln) for ln in self.lines) and "## 附录" in self.raw:
            return "lecture_v3"
        return "unknown"

    def body_lines(self):
        return [(i + 1, ln) for i, ln in enumerate(self.lines) if not self.in_code[i]]

    def section_span(self, pattern):
        """返回以 pattern 开头的节的范围 (start_idx, end_idx)，找不到返回 None。"""
        start = None
        for i, ln in enumerate(self.lines):
            if re.match(pattern, ln):
                start = i
                break
        if start is None:
            return None
        end = start + 1
        while end < self.n and not re.match(r"^#{1,3}\s", self.lines[end]):
            end += 1
        return start, end

    def selfcheck_start(self):
        """「交付前自检清单」节起始行号（1 基），无则 None；兼容「附录 C　」前缀。"""
        for i, ln in enumerate(self.lines):
            if re.match(r"^#+.*交付前自检清单", ln):
                return i + 1
        return None

    @staticmethod
    def sec_pat(name):
        """节标题正则，允许「五、」「四.」等章节序号前缀。"""
        return r"^#+\s*(?:[〇零一二三四五六七八九十百0-9]+[、.．]?\s*)?" + name

    # ---------- 通用检查 ----------
    def check_frontmatter(self):
        fm = self.frontmatter()
        if fm is None:
            self.add("C01", FAIL, "缺 YAML frontmatter（首行不是 ---）")
            return
        miss = [k for k in HEAD_KEYS if k not in fm]
        if miss:
            self.add("C01", FAIL, "frontmatter 缺项：" + " / ".join(miss))
        else:
            self.add("C01", PASS, "frontmatter 必备项齐全")

    def check_emoji(self):
        seqs = []
        for i, ln in enumerate(self.lines):
            for ch in ln:
                o = ord(ch)
                if o == VS16:
                    continue
                if any(a <= o <= b for a, b in EMOJI_RANGES):
                    seqs.append((i + 1, ch, o))
        if self.kind in ("review_v1", "review_v2", "review_v2_1"):
            bad = [s for s in seqs if s[2] not in REVIEW_ALLOWED]
            if bad:
                loc = ", ".join("L%d %s" % (b[0], b[1]) for b in bad[:5])
                self.add("C02", FAIL, "复习版出现特许外 emoji：%s" % loc, bad[0][0])
            elif len(seqs) > 15:
                self.add("C02", FAIL, "限量档 emoji %d 个 > 15" % len(seqs), seqs[0][0])
            else:
                self.add("C02", PASS, "emoji %d 个（限量档合规：仅 ❌✅⭐⚠️）" % len(seqs))
        else:
            if seqs:
                loc = ", ".join("L%d U+%04X" % (s[0], s[2]) for s in seqs[:5])
                self.add("C02", FAIL, "出现 emoji %d 处：%s" % (len(seqs), loc), seqs[0][0])
            else:
                self.add("C02", PASS, "全文无 emoji")

    def check_callouts(self):
        blocks = []
        cur = []
        for i, ln in enumerate(self.lines):
            if self.in_code[i]:
                continue
            if ln.startswith(">"):
                cur.append((i + 1, ln))
            else:
                if cur:
                    blocks.append(cur)
                cur = []
        if cur:
            blocks.append(cur)

        inline = []      # 声明行未独占一行
        folded = []      # 折叠语法
        badtype = []     # 非法类型
        multi = []       # 同块多主标签
        total = 0
        for blk in blocks:
            decls = []
            for no, ln in blk:
                m = re.match(r"^>\s*\[!([A-Za-z]+)\]([-+]?)\s*(.*)$", ln)
                if m:
                    total += 1
                    t = m.group(1).lower()
                    decls.append(no)
                    # 折叠标记 -/+ 合法（2026-09-25 渲染口径：Obsidian 优先，检索练习用）；
                    # 折叠声明行同样受 C05b「独占一行」约束（行尾不得带标题文字）
                    if t not in CALLOUT_OK:
                        badtype.append((no, m.group(1)))
                    if m.group(3).strip():
                        inline.append(no)
            if len(decls) > 1:
                multi.append(decls[0])

        probs = []
        if badtype:
            probs.append("类型非法：" + ", ".join("L%d [!%s]" % (n, t) for n, t in badtype[:5]))
        if probs:
            self.add("C05", FAIL, "callout " + "；".join(probs),
                     badtype[0][0])
        else:
            self.add("C05", PASS, "callout 类型合法（%d 处）" % total)

        if inline:
            self.add("C05b", FAIL, "callout 声明行未独占一行：L" + ", L".join(map(str, inline[:5])), inline[0])
        else:
            self.add("C05b", PASS, "callout 声明行均独占一行")

        if multi:
            self.add("C06", FAIL, "同一引用块出现多个主标签：L" + ", L".join(map(str, multi[:5])), multi[0])
        else:
            self.add("C06", PASS, "同块单主标签")

    def check_headings(self):
        lv = [(i + 1, len(m.group(1))) for i, ln in self.body_lines()
              for m in [re.match(r"^(#{1,6})\s+\S", ln)] if m]
        bad = []
        prev = 0
        for no, l in lv:
            if prev and l > prev + 1:
                bad.append((no, prev, l))
            prev = l
        if bad:
            msg = "标题跳级：" + ", ".join("L%d H%d→H%d" % b for b in bad[:5])
            self.add("C03", FAIL, msg, bad[0][0])
        else:
            self.add("C03", PASS, "标题不跳级（%d 个标题）" % len(lv))

    def check_tables(self):
        over = []
        for i, ln in self.body_lines():
            s = ln.strip()
            if s.startswith("|") and s.endswith("|") and s.count("|") >= 2:
                # 单元格内的转义竖线 \| 不计为列分隔（行内代码含位运算 | 时会误判）
                cols = len([c for c in s.replace("\\|", "\x01").split("|")[1:-1]])
                if cols > 6:
                    over.append((i, cols))
        if over:
            msg = "表格超 6 列：" + ", ".join("L%d(%d列)" % o for o in over[:5])
            self.add("C04", FAIL, msg, over[0][0])
        else:
            self.add("C04", PASS, "表格均 ≤6 列")

    def check_links(self):
        # 口径（2026-09-25 用户裁决）：Obsidian 为主战场，GitHub 仅上传备份；[[]] 双链与块嵌入解禁
        cut = self.selfcheck_start() or (self.n + 1)
        cnt = 0
        for i, ln in self.body_lines():
            if i >= cut:
                continue
            stripped = re.sub(r"`[^`]*`", "", ln)   # 剔除行内代码，避免规则文案误报
            cnt += stripped.count("[[")
        self.add("C07", PASS, "[[]] 双链已解禁（Obsidian 优先口径，%d 处）" % cnt)

    def check_code_blocks(self):
        if self.unclosed:
            self.add("C09", FAIL, "代码围栏未闭合（``` 计数为奇数）")
            return
        nolang = [s + 1 for lang, s, e in self.fences if not lang]
        if nolang:
            self.add("C09", FAIL, "代码块缺语言标记：L" + ", L".join(map(str, nolang[:5])), nolang[0])
        else:
            self.add("C09", PASS, "代码块均有语言标记（%d 块）" % len(self.fences))

        if self.kind == "review_v2":
            # v2.0 框架卡片体：代码模板（cpp 等）≤12 行硬上限；文本树 ≤40 行软上限
            hard, soft = [], []
            for lang, s, e in self.fences:
                body = e - s - 1
                if lang and lang != "text" and lang != "mermaid" and body > 12:
                    hard.append((s + 1, lang, body))
                elif lang == "text" and body > 40:
                    soft.append((s + 1, lang, body))
            if hard:
                msg = "代码模板超 12 行：" + ", ".join("L%d(%s,%d行)" % o for o in hard[:5])
                self.add("C09b", FAIL, msg, hard[0][0])
            else:
                self.add("C09b", PASS, "代码模板均 ≤12 行")
            if soft:
                msg = "文本树超 40 行：" + ", ".join("L%d(%s,%d行)" % o for o in soft[:5])
                self.add("C09d", WARN, msg, soft[0][0])
        elif self.kind == "review_v1":
            # v1.1：12 行上限只约束「高频代码模板」节；其余文本树按 40 行软上限提醒
            tpl = self.section_span(self.sec_pat("高频代码模板"))
            if not tpl:
                tpl = self.section_span(r"^#+.*代码模板")
            tpl_start, tpl_end = (tpl[0], tpl[1]) if tpl else (0, 0)
            if not tpl:
                self.add("C09c", FAIL, "复习版缺「高频代码模板」节")
            hard, soft = [], []
            for lang, s, e in self.fences:
                body = e - s - 1
                if tpl and tpl_start <= s < tpl_end:
                    if body > 12:
                        hard.append((s + 1, lang, body))
                elif body > 40:
                    soft.append((s + 1, lang, body))
            if hard:
                msg = "模板节代码块超 12 行：" + ", ".join("L%d(%s,%d行)" % o for o in hard[:5])
                self.add("C09b", FAIL, msg, hard[0][0])
            else:
                self.add("C09b", PASS, "模板节代码块均 ≤12 行")
            if soft:
                msg = "非模板节文本树超 40 行：" + ", ".join("L%d(%s,%d行)" % o for o in soft[:5])
                self.add("C09d", WARN, msg, soft[0][0])
        else:
            cap = 60
            over = [(s + 1, lang, e - s - 1) for lang, s, e in self.fences if e - s - 1 > cap]
            if over:
                msg = "代码块超 %d 行：" % cap + ", ".join("L%d(%s,%d行)" % o for o in over[:5])
                self.add("C09b", FAIL, msg, over[0][0])
            else:
                self.add("C09b", PASS, "代码块均 ≤%d 行" % cap)

    def check_mermaid(self):
        mm = [(s, e) for lang, s, e in self.fences if lang == "mermaid"]
        cap = {"lecture_v3": 3, "lecture_v2": 2}.get(self.kind, 1)
        if len(mm) > cap:
            self.add("C10", FAIL, "mermaid %d 个 > 上限 %d" % (len(mm), cap), mm[0][0] + 1)
        else:
            self.add("C10", PASS, "mermaid %d 个（≤%d）" % (len(mm), cap))
        tail = []
        for s, e in mm:
            ctx = "\n".join(self.lines[e + 1:e + 14])
            if "文字版" not in ctx and "文字推导" not in ctx:
                tail.append(s + 1)
        if tail:
            self.add("C10b", WARN, "mermaid 后未见文字版兜底：L" + ", L".join(map(str, tail)), tail[0])
        elif mm:
            self.add("C10b", PASS, "mermaid 均配文字版")

    def check_tail(self):
        miss = []
        if not re.search(self.sec_pat("自测清单"), self.raw, re.M):
            miss.append("自测清单")
        if not re.search(self.sec_pat("错题登记"), self.raw, re.M):
            miss.append("错题登记")
        if miss:
            self.add("C08", FAIL, "尾部缺节：" + " / ".join(miss))
        else:
            self.add("C08", PASS, "尾部自测清单 + 错题登记齐全")

    def check_selfcheck(self):
        if self.selfcheck_start() is not None:
            self.add("C12", PASS, "含交付前自检清单节")
        else:
            self.add("C12", FAIL, "缺「交付前自检清单」节")

    def check_ban_words(self):
        cut = self.selfcheck_start() or (self.n + 1)
        hits = [(i + 1, w) for i, ln in self.body_lines() if i < cut for w in BAN_WORDS if w in ln]
        if hits:
            msg = "出现跳过推导措辞：" + ", ".join("L%d「%s」" % h for h in hits[:5])
            self.add("C11", WARN, msg, hits[0][0])
        else:
            self.add("C11", PASS, "无「显然 / 易得 / 略」类措辞")

    # ---------- 讲解笔记专属 ----------
    def check_lecture(self):
        if self.kind == "lecture_v3":
            self.check_lecture_v3()
        else:
            self.check_lecture_v2()

    def check_lecture_v3(self):
        """v3.0 格式：### N. 小节 + 附录 A/B/C；N 对 N 用附录 A-2 对账。"""
        kt = [i for i, ln in enumerate(self.lines) if re.match(r"^###\s*\d+\.\s*\S", ln)]
        span = self.section_span(r"^#+.*A-2")
        n_decl = None
        if span:
            a, b = span
            n_decl = sum(1 for ln in self.lines[a:b]
                         if re.match(r"^\|\s*\d+\s*\|", ln.strip())
                         or re.match(r"^(?:[-*]\s*)?\d+[.、]\s*\S", ln.strip()))
        if not kt:
            self.add("L01", FAIL, "未找到 ### N. 知识点小节")
        elif n_decl is None:
            self.add("L01", FAIL, "未找到附录 A-2 知识点总清单节")
        elif n_decl != len(kt):
            self.add("L01", FAIL, "N 对 N 不符：附录总清单 %d 条 vs 正文 %d 节" % (n_decl, len(kt)))
        else:
            self.add("L01", PASS, "N 对 N 对账一致（%d 条 = %d 节）" % (n_decl, len(kt)))

        seg_spans = []
        for j, s in enumerate(kt):
            e = kt[j + 1] if j + 1 < len(kt) else self.n
            seg_spans.append((s, e))

        miss6 = []
        for s, e in seg_spans:
            seg = "\n".join(self.lines[s:e])
            lack = [c for c in SEG_MARKS if c not in seg]
            if lack:
                miss6.append((self.lines[s].strip()[:24], "".join(lack)))
        if miss6:
            msg = "六步不全：" + ", ".join("%s 缺 %s" % m for m in miss6[:5])
            self.add("L02", FAIL, msg)
        else:
            self.add("L02", PASS, "各知识点六步齐全（%d 节）" % len(kt))

        for name, code, label in [("附录", "L03", "附录区（对账/假设/自检）"),
                                  ("坑点总表", "L06", "全篇坑点总表节"),
                                  ("总结与自测", "L09", "总结与自测节")]:
            ok = bool(re.search(r"^#+.*" + name, self.raw, re.M))
            self.add(code, PASS if ok else FAIL, ("存在" if ok else "缺") + label)

        notab = []
        for s, e in seg_spans:
            seg = "\n".join(self.lines[s:e])
            if "|" not in seg and "性质" not in seg and "复杂度" not in seg:
                notab.append(self.lines[s].strip()[:24])
        if notab:
            self.add("L07", WARN, "未见性质交代（表/性质/复杂度字样）：" + ", ".join(notab[:5]))
        else:
            self.add("L07", PASS, "各知识点含性质交代")

        nomo = []
        for s, e in seg_spans:
            seg = "\n".join(self.lines[s:e])
            if not any(w in seg for w in ("设计动机", "为什么", "为何", "原因")):
                nomo.append(self.lines[s].strip()[:24])
        if nomo:
            self.add("L08", WARN, "未见动机解释：" + ", ".join(nomo[:5]))
        else:
            self.add("L08", PASS, "各知识点含动机/原理解释")

        if "编译验证" in self.raw or "实测" in self.raw:
            self.add("L10", PASS, "含本地编译验证/实测记录")
        else:
            self.add("L10", WARN, "未见编译验证或实测记录")

    def check_lecture_v2(self):
        kt = [i for i, ln in enumerate(self.lines) if re.match(r"^###\s*K-\d+", ln)]
        span = self.section_span(r"^###\s*0-2")
        n_decl = None
        if span:
            a, b = span
            n_decl = sum(1 for ln in self.lines[a:b] if re.match(r"^\|\s*\d+\s*\|", ln.strip()))
        if not kt:
            self.add("L01", FAIL, "未找到 K-x 知识点小节")
        elif n_decl is None:
            self.add("L01", FAIL, "未找到 0-2 知识点总清单节")
        elif n_decl != len(kt):
            self.add("L01", FAIL, "N 对 N 不符：总清单 %d 条 vs 正文 %d 节" % (n_decl, len(kt)))
        else:
            self.add("L01", PASS, "N 对 N 对账一致（%d 条 = %d 节）" % (n_decl, len(kt)))

        seg_spans = []
        for j, s in enumerate(kt):
            e = kt[j + 1] if j + 1 < len(kt) else self.n
            seg_spans.append((s, e))

        miss6 = []
        for s, e in seg_spans:
            seg = "\n".join(self.lines[s:e])
            lack = [c for c in SEG_MARKS if c not in seg]
            if lack:
                miss6.append((self.lines[s].strip()[:24], "".join(lack)))
        if miss6:
            msg = "六段不全：" + ", ".join("%s 缺 %s" % m for m in miss6[:5])
            self.add("L02", FAIL, msg)
        else:
            self.add("L02", PASS, "各 K 节六段齐全（%d 节）" % len(kt))

        for pat, code, label in [(r"^###\s*0-4", "L03", "预备概念节"),
                                 (r"^###\s*0-3", "L04", "冲突登记节"),
                                 (r"^##\s*四、", "L05", "假设与缺口登记节"),
                                 (r"^##\s*二、", "L06", "本篇易错总表节"),
                                 (r"^##\s*三、", "L09", "前置概念清单节")]:
            self.add(code, PASS if self.section_span(pat) else FAIL,
                     ("存在" if self.section_span(pat) else "缺") + label)

        notab = []
        for s, e in seg_spans:
            seg = "\n".join(self.lines[s:e])
            if "|" not in seg and "性质表" not in seg:
                notab.append(self.lines[s].strip()[:24])
        if notab:
            self.add("L07", WARN, "未见表/免表说明：" + ", ".join(notab[:5]))
        else:
            self.add("L07", PASS, "各 K 节含表格或免表说明")

        nomo = []
        for s, e in seg_spans:
            seg = "\n".join(self.lines[s:e])
            if not any(w in seg for w in ("设计动机", "为什么", "为何", "原因")):
                nomo.append(self.lines[s].strip()[:24])
        if nomo:
            self.add("L08", WARN, "未见动机解释：" + ", ".join(nomo[:5]))
        else:
            self.add("L08", PASS, "各 K 节含动机/原理解释")

        if "编译验证" in self.raw or "实测" in self.raw:
            self.add("L10", PASS, "含本地编译验证/实测记录")
        else:
            self.add("L10", WARN, "未见编译验证或实测记录")

    # ---------- 复习回顾版专属 ----------
    def check_review(self):
        if self.kind == "review_v2_1":
            self.check_review_v2_1()
        elif self.kind == "review_v2":
            self.check_review_v2()
        else:
            self.check_review_v1()

    def check_review_v2_1(self):
        """v2.1 六步详略对照体（无行数上限；600 行/12 行硬约束已随 v2.0 废除）。"""
        cnt = len(re.findall(r"P[012]", self.raw))
        if cnt >= 3:
            self.add("R01", PASS, "含 P0/P1/P2 优先级标注（%d 处）" % cnt)
        else:
            self.add("R01", FAIL, "未见 P0/P1/P2 优先级标注")

        sections = ["知识地图", "知识点逐卡", "易错总表", "待补知识点清单", "口诀集", "自测清单", "问题日志"]
        miss = [s for s in sections if s not in self.raw]
        if miss:
            self.add("R03", FAIL, "缺必备节：" + " / ".join(miss))
        else:
            self.add("R03", PASS, "必备七节齐全（地图/逐卡/易错/待补/口诀/自测/问题日志）")

        seg_spans = []
        for i, ln in enumerate(self.lines):
            if re.match(r"^###\s*【P0】", ln):
                j = i + 1
                while j < self.n and not re.match(r"^#{1,3}\s", self.lines[j]):
                    j += 1
                seg_spans.append((i, j))
        nosig = []
        nofold = []
        for s, e in seg_spans:
            seg = "\n".join(self.lines[s:e])
            if "识别信号" not in seg:
                nosig.append(self.lines[s].strip()[:24])
            if "边界数据集" in seg and "[!example]-" not in seg and "[!note]-" not in seg:
                nofold.append(self.lines[s].strip()[:24])
        if seg_spans and nosig:
            self.add("R05", FAIL, "P0 卡缺「识别信号」：" + ", ".join(nosig[:5]))
        elif seg_spans:
            self.add("R05", PASS, "P0 卡均含识别信号（%d 张）" % len(seg_spans))
        else:
            self.add("R05", WARN, "未见 P0 卡")
        if nofold:
            self.add("R06", WARN, "边界数据集未用折叠 callout（[!example]- 或 [!note]-）：" + ", ".join(nofold[:5]))
        else:
            self.add("R06", PASS, "边界数据集折叠呈现（或未涉及）")

        if "最后复习日期" in self.raw:
            self.add("R07", PASS, "frontmatter 含「最后复习日期」")
        else:
            self.add("R07", WARN, "frontmatter 缺「最后复习日期」字段")

        six = [c for c in "①②③④⑤⑥" if c in self.raw]
        if len(six) == 6:
            self.add("R08", PASS, "六步标记齐全（详略对照体）")
        else:
            self.add("R08", FAIL, "六步标记残缺（缺 %s）" % "".join(c for c in "①②③④⑤⑥" if c not in six))

        n_text = len([1 for lang, _, _ in self.fences if lang == "text"])
        n_mm = len([1 for lang, _, _ in self.fences if lang == "mermaid"])
        if n_text >= n_mm:
            self.add("R04", PASS, "文本树 %d 个 ≥ mermaid %d 个" % (n_text, n_mm))
        else:
            self.add("R04", FAIL, "文本树 %d < mermaid %d" % (n_text, n_mm))

    def check_review_v2(self):
        """v2.0 框架卡片体。"""
        cnt = len(re.findall(r"P[012]", self.raw))
        if cnt >= 3:
            self.add("R01", PASS, "含 P0/P1/P2 优先级标注（%d 处）" % cnt)
        else:
            self.add("R01", FAIL, "未见 P0/P1/P2 优先级标注")

        if self.n <= 600:
            self.add("R02", PASS, "全篇 %d 行（≤600）" % self.n)
        else:
            self.add("R02", FAIL, "全篇 %d 行 > 600" % self.n)

        sections = ["知识地图", "框架卡片", "易错总表", "待补知识点清单", "口诀集", "自测清单", "错题登记"]
        miss = [s for s in sections if s not in self.raw]
        if miss:
            self.add("R03", FAIL, "缺必备节：" + " / ".join(miss))
        else:
            self.add("R03", PASS, "必备七节齐全（地图/卡片/易错/待补/口诀/自测/错题）")

        p0 = [i for i, ln in enumerate(self.lines) if re.match(r"^#+\s*【P0】", ln)]
        nosig = []
        for j, s in enumerate(p0):
            e = p0[j + 1] if j + 1 < len(p0) else self.n
            seg = "\n".join(self.lines[s:e])
            if "识别信号" not in seg:
                nosig.append(self.lines[s].strip()[:24])
        if p0 and nosig:
            self.add("R05", FAIL, "P0 卡缺「识别信号」：" + ", ".join(nosig[:5]))
        elif p0:
            self.add("R05", PASS, "P0 框架卡片均含识别信号（%d 张）" % len(p0))
        else:
            self.add("R05", WARN, "未见 P0 框架卡片")

        n_text = len([1 for lang, _, _ in self.fences if lang == "text"])
        n_mm = len([1 for lang, _, _ in self.fences if lang == "mermaid"])
        if n_text >= n_mm:
            self.add("R04", PASS, "文本树 %d 个 ≥ mermaid %d 个" % (n_text, n_mm))
        else:
            self.add("R04", FAIL, "文本树 %d < mermaid %d" % (n_text, n_mm))

    def check_review_v1(self):
        cnt = len(re.findall(r"P[012]", self.raw))
        if cnt >= 3:
            self.add("R01", PASS, "含 P0/P1/P2 优先级标注（%d 处）" % cnt)
        else:
            self.add("R01", FAIL, "未见 P0/P1/P2 优先级标注")

        if self.n <= 600:
            self.add("R02", PASS, "全篇 %d 行（≤600）" % self.n)
        else:
            self.add("R02", FAIL, "全篇 %d 行 > 600" % self.n)

        miss = [s for s in REVIEW_SECTIONS if s not in self.raw]
        if miss:
            self.add("R03", FAIL, "缺必备节：" + " / ".join(miss))
        else:
            self.add("R03", PASS, "必备五节齐全（框架树/待补清单/口诀集/自测/错题）")

        n_text = len([1 for lang, _, _ in self.fences if lang == "text"])
        n_mm = len([1 for lang, _, _ in self.fences if lang == "mermaid"])
        if n_text >= n_mm:
            self.add("R04", PASS, "文本树 %d 个 ≥ mermaid %d 个" % (n_text, n_mm))
        else:
            self.add("R04", FAIL, "文本树 %d < mermaid %d" % (n_text, n_mm))

    # ---------- 调度 ----------
    def run(self):
        self.check_frontmatter()
        self.check_emoji()
        self.check_callouts()
        self.check_headings()
        self.check_tables()
        self.check_links()
        self.check_code_blocks()
        self.check_mermaid()
        self.check_tail()
        self.check_selfcheck()
        self.check_ban_words()
        if self.kind in ("lecture_v2", "lecture_v3"):
            self.check_lecture()
        elif self.kind in ("review_v1", "review_v2", "review_v2_1"):
            self.check_review()
        return self


def render(notes, verbose=False):
    out = []
    out.append("学习工程 · 笔记 lint 报告")
    out.append("生成时间：" + datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
    out.append("=" * 72)
    tot = {PASS: 0, FAIL: 0, WARN: 0}
    for nt in notes:
        c = {PASS: 0, FAIL: 0, WARN: 0}
        for _, st, _, _ in nt.results:
            c[st] += 1
            tot[st] += 1
        state = "通过" if c[FAIL] == 0 else "未通过"
        out.append("[%s] %s   类型：%s   行数：%d   结果：%s" %
                   (state, nt.name, nt.kind_label, nt.n, "PASS" if c[FAIL] == 0 else "FAIL"))
        for code, st, msg, line in nt.results:
            if st == PASS and not verbose:
                continue
            loc = (" L%d" % line) if line else ""
            out.append("  [%s] %-5s%s %s" % (st, code, loc, msg))
        out.append("  小计：%d PASS / %d FAIL / %d WARN" % (c[PASS], c[FAIL], c[WARN]))
        out.append("-" * 72)
    out.append("汇总：%d 个文件 / %d PASS / %d FAIL / %d WARN" %
               (len(notes), tot[PASS], tot[FAIL], tot[WARN]))
    if tot[FAIL]:
        out.append("结论：存在 FAIL，需修订后再交付。")
    else:
        out.append("结论：全部通过（WARN 项建议人工确认）。")
    return "\n".join(out)


def collect(targets, base_dir):
    files = []
    for t in targets:
        p = t if os.path.isabs(t) else os.path.join(os.getcwd(), t)
        if os.path.isdir(p):
            for f in sorted(os.listdir(p)):
                if f.lower().endswith(".md") and not f.startswith("_"):
                    files.append(os.path.join(p, f))
        elif os.path.isfile(p):
            files.append(p)
    if not files:
        notes_dir = base_dir
        if os.path.isdir(notes_dir):
            for f in sorted(os.listdir(notes_dir)):
                if f.lower().endswith(".md") and not f.startswith("_"):
                    files.append(os.path.join(notes_dir, f))
    return files


def main():
    here = os.path.dirname(os.path.abspath(__file__))
    default_notes = os.path.join(os.path.dirname(here), "笔记")
    ap = argparse.ArgumentParser(description="学习工程笔记 lint（自检清单机器化）")
    ap.add_argument("targets", nargs="*", help="文件或目录；缺省扫描 学习工程\\笔记\\")
    ap.add_argument("-o", "--out", help="报告输出文件（UTF-8）")
    ap.add_argument("-v", "--verbose", action="store_true", help="输出全部条目（含 PASS）")
    args = ap.parse_args()

    files = collect(args.targets, default_notes)
    if not files:
        print("未找到待检查的 md 文件。")
        return 2
    notes = [Note(f).run() for f in files]
    text = render(notes, args.verbose)
    try:
        sys.stdout.reconfigure(encoding="utf-8", errors="replace")
    except Exception:
        pass
    print(text)
    if args.out:
        with open(args.out, "w", encoding="utf-8") as f:
            f.write(text)
    return 1 if any(st == FAIL for nt in notes for _, st, _, _ in nt.results) else 0


if __name__ == "__main__":
    sys.exit(main())
