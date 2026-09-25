---
tags: [算法竞赛, STL, 复习回顾]
优先级: P0
掌握状态: 未学
来源: STL容器与算法手册.docx（素材\STL容器与算法手册\）
生成日期: 2026-09-24
---

# STL 容器与算法 · 复习回顾版

> **定位**：核心知识点的浓缩重组，供快速回顾与自查。详细推导见原手册（23.01–23.18）。
> **排版特许**：本文件按用户许可使用**少量** emoji（仅 ❌ / ✅ / ⭐ / ⚠️，全篇 ≤ 15 个）；其余标注遵循学习工程均衡档。

---

## 一、知识框架总览

```text
STL 六大组件
├─ 容器（装数据的）
│  ├─ 序列容器 ………… string · vector · deque · list
│  ├─ 容器适配器 …… stack · queue（priority_queue 本手册未覆盖，见第七节）
│  └─ 关联容器 ……… set · multiset · map · multimap（红黑树，自动有序）
│     （unordered 系列只有补充区一笔带过，见第七节）
├─ 算法（处理数据的） … for_each · transform · find 系 · 二分系
├─ 迭代器（容器与算法之间的桥） … 随机访问 > 双向 > 单向
├─ 仿函数与谓词（定制规则） … greater · lambda · 自定义 cmp
└─ 适配器 / 配置器 ………… 本手册未展开
```

```text
横贯概念（手册第零部分，所有容器共用）
0.1 迭代器（左闭右开 [begin, end)）
0.2 UB（空容器访问 = 未定义行为）
0.3 扩容与均摊 O(1)（1→2→4→8，总搬运 < 2n）
0.4 迭代器失效表
0.5 lambda / 仿函数 / 谓词
0.6 size_t 无符号陷阱（size()-1 空时回绕成巨数）
0.7 字典序（逐个比，前缀相同短的小）
```

---

## 二、横贯概念速记

| 概念 | 一句话 | 必背点 | 优先级 |
|------|--------|--------|--------|
| 迭代器 | 广义指针，算法只认它不认容器 | `it - v.begin()` 得下标 ⭐；`v.end()` 是哨兵，解引用 UB | P0：一切容器与算法的通用接口 |
| UB | 标准不管后果，换环境就变样 | `front/back/top/pop/[]` 之前先想「会不会是空的」 | P0：空容器访问是 RE 第一大来源 |
| 均摊 O(1) | 翻倍扩容，总搬运 < 2n | 扩容瞬间**全部**迭代器/指针/引用失效 | P1：复杂度分析概念，不直接写题但要能解释 |
| lambda | 匿名函数 `[] (参数) { 函数体 }` | 捕获：`[]` 不带 / `[x]` 按值 / `[&]` 按引用 | P0：sort 自定义 cmp 的高频写法 |
| size_t | 无符号，没有负数 | `size()` 参与减法前先判 `> 0` | P0：size()-1 回绕是经典 WA 来源 |
| 字典序 | string 与 pair 共用的比较规则 | pair 先比 first 再比 second → 排序免写 cmp | P1：排序去 cmp 的原理，概念题会考 |

> 优先级口径（对齐《复习回顾版生成_提示词》v1.1）：P0 = 每场必用或 RE / WA 高危；P1 = 固定题型或概念辨析高频；P2 = 竞赛写题几乎不用，了解概念即可。

**迭代器三档能力（决定容器能干什么）**

| 档位 | 能力 | 拥有者 |
|------|------|--------|
| 随机访问 | `it+n`、`it1-it2` | vector、string、deque |
| 双向 | 只有 `++`、`--` | list、set、map |
| 单向 | 只有 `++` | unordered 系列 |

> [!warning]
> **【难点】** 这张表解释三个经典问题：list 不能 `std::sort`（要随机访问）、erase 要写 `v.begin()+2`（数字只是偏移量）、set 用全局 `lower_bound` 是 $O(n)$（迭代器不能跳）。

**迭代器失效表（必背）**

| 容器 | 操作 | 失效范围 |
|------|------|---------|
| vector | 扩容 | 全部 |
| vector | 中间 insert/erase | 操作点之后全部 |
| list | insert | 不失效 |
| list | erase | 只被删的那个 |
| set/map | insert | 不失效 |
| set/map | erase | 只被删的那个 |

---

## 三、容器速查树

### 3.1 序列容器

```text
string（连续字符数组 ≈ vector<char>）【P0】
├─ 判定依据：每场必用，读入输出与文本处理的基础设施
├─ 核心：随机访问 O(1)；拼接首选 +=；比较走字典序
├─ 参数模式：substr / erase / replace 全是「起点 + 长度」制
│   └─ 闭区间 [a,b] → s.substr(a, b - a + 1)
├─ find 失败返回 string::npos（= size_t(-1) 回绕巨数）
│   └─ 判定唯一写法：pos == string::npos；npos + 1 会回绕成 0 ⚠️
└─ 首坑："a" + "b" ❌（两个 const char* 不能加）；s + "a" ✅
```

```text
vector（连续内存、自动扩容的数组）【P0】
├─ 判定依据：竞赛第一容器，动态数组与二维图存储无处不在
├─ 三指针：begin / end / cap → size = end - begin，capacity = cap - begin
├─ 初始化陷阱：v(5) = 5 个 0；v{5} = 一个元素 5（圆括号个数、花括号列表）
├─ 二维：vector<vector<int>> g(n, vector<int>(m, 0))
│   └─ 外层填充值本身必须是一个 vector<int>，不能只写 m
├─ reserve vs resize：reserve 只扩车位（v[i] 仍 UB）；resize 真造元素
├─ erase-remove 惯用法：内层「挤」外层「删」，缺一不可
└─ 访问：v[i] 不查越界；v.at(i) 抛异常；空 vector 一切访问是 UB
```

```text
deque（分段连续 + 中控 map，两端 O(1)）【P1】
├─ 判定依据：主要出场是单调队列底座与双端操作题型，频率低于 vector
├─ 比 vector 多：push_front / pop_front 也是 O(1)
├─ 滑动窗口最值：存【下标】不存值（要算 dq.front() <= i-k）
└─ 三步口诀：① 弹出滑出窗口的 ② 尾部弹出破坏单调的 ③ 入队，队首即答案
```

```text
list（双向链表，节点 = 值 + 前驱 + 后继）【P2】
├─ 判定依据：竞赛写题几乎不用（vector 可替代且缓存友好），概念辨析题偶尔考
├─ 不支持 []、不能 it+3，只能 ++ / --
├─ lt.sort() 是成员函数（归并 O(n log n)，且稳定）；std::sort 用不了
├─ lt.remove(x) 真删（对比 vector 的全局 remove 只挤不删）
├─ unique 只去【相邻】重复 → 先 sort 再 unique
└─ 为什么平时还是用 vector：list 找位置本身 O(n) + 缓存不友好
```

### 3.2 容器适配器（封死口子，用限制换安全）

```text
stack（LIFO，默认底层 deque）【P0】    queue（FIFO，默认底层 deque）【P0】
├─ 判定依据：stack 管单调栈/括号匹配/显式 DFS，queue 管 BFS/拓扑排序——主场题型必用
├─ 只有 push / top / pop               ├─ 只有 push / front / back / pop
├─ pop 返回 void → 先 top() 再 pop()   ├─ pop 返回 void → 先 front() 再 pop()
├─ 无迭代器，只能清空式遍历             ├─ 无迭代器，只能清空式遍历
└─ 应用：括号匹配、单调栈               └─ 应用：BFS（入队即标记）、拓扑排序
```

### 3.3 关联容器（红黑树，全部 O(log n)，中序遍历 = 升序）

```text
set（自动排序 + 自动去重，元素 const 不可改）【P0】
├─ 判定依据：去重排序与有序集合维护，判重/动态有序场景高频
├─ 查找：s.find / s.count；最值 *s.begin() / *s.rbegin()
├─ lower_bound 必须用成员版（全局版 O(n) 假二分）⚠️
└─ 改元素：只能 erase 再 insert

multiset（允许重复）【P1】
├─ 判定依据：带重复元素的有序维护（多插入删除取最值），题型固定
└─ erase(值) = 删光；erase(迭代器) = 删一个 → 删一个先 find 判 end 再删

map（键→值有序映射）【P0】
├─ 判定依据：计数与映射的高频载体，m[k] 插入陷阱是必防坑
├─ 插入三形态：m[k]=v 覆盖 / insert 不覆盖 / emplace 同 insert
├─ 最著名的坑：m[k] 纯查询也会【插入】默认值 → 判存在只用 count / find
├─ 计数套路：for (int x : a) cnt[x]++;（正好利用 [] 插 0）
└─ 遍历最清爽：for (auto &[k, v] : m)（C++17 结构化绑定）

multimap（键可重复，没有 [] 和 at()）【P2】
├─ 判定依据：竞赛几乎不用（map + vector 可替代），equal_range 概念了解即可
└─ 取同键全部值：equal_range 得 pair{lower, upper}，区间遍历

pair / tuple（值类型，不是容器）【P0】
├─ 判定依据：坐标/边/多关键字排序的通用载体，无处不在
├─ pair 自带字典序比较 → 想按谁排序就把谁放 first
└─ tuple：get<0>(t)，尖括号里必须是编译期常量
```

---

## 四、算法速查

| 算法 | 复杂度 | 前提 | 返回 | 优先级 |
|------|--------|------|------|--------|
| find / find_if | $O(n)$ | 无 | 迭代器（失败 = end()） | P1：手写循环可替代，识别用法即可 |
| count / count_if | $O(n)$ | 无 | 个数 | P1：同上，一行省事 |
| binary_search | $O(\log n)$ | 有序 | bool（只判有无） | P0：二分系核心，有序判存在高频 |
| lower_bound | $O(\log n)$ | 有序 | 第一个 $\geq x$ | P0：二分系核心，要下标必用 |
| upper_bound | $O(\log n)$ | 有序 | 第一个 $> x$ | P0：二分系核心，去重划分必用 |

```text
要下标的判定模板（binary_search 给不了位置时）
└─ auto pos = lower_bound(v.begin(), v.end(), x);
   if (pos != v.end() && *pos == x) { int idx = pos - v.begin(); }
```

- `for_each`（P2：范围 for 可完全替代，看懂即可）：想改元素，lambda 参数必须写引用 `[](int &x){ x *= 2; }`
- `transform`（P2：手写循环可替代，back_inserter 概念了解）：目标容器**必须先开空间**（`vector<int> res(v.size())`），否则越界 UB

---

## 五、四个高频代码模板（逻辑关系图）

```text
边遍历边删（vector / map 通用）【P1：删除类题型的固定写法】
└─ for (auto it = c.begin(); it != c.end(); )
      条件成立 → it = c.erase(it)   ← erase 返回下一个有效位置
      否则     → ++it
      （erase 后 ++it ❌，it 已失效）
```

```text
BFS（queue）【P0：图论最短步数标准工具】
└─ 起点入队 + 标记 → while 队非空：
      取出队首 → 遍历邻居：
          未访问 → 标记 + 入队
      关键：标记在【入队时】，出队才标记会重复入队
```

```text
单调栈（stack，下一个更大元素）【P0：下一个更大/更小元素题型模板】
└─ for i in 1..n：
      while 栈非空 且 a[栈顶] < a[i]：ans[栈顶] = i，弹栈
      i 入栈
      （栈内对应值保持单调递减；严格用 <，非严格用 <=，用反就错）
```

```text
单调队列（deque，滑动窗口最小值）【P1：固定窗口最值题型模板】
└─ for i in 1..n：
      ① 队首下标 ≤ i-k → 弹出（滑出窗口）
      ② 队尾对应值 ≥ a[i] → 弹出（保持单调递增）
      ③ i 入队尾
      ④ i ≥ k 时，队首即窗口最小值
```

---

## 六、终极易错 20 条（原手册浓缩，编号可回查）

| # | 坑 | 正解 |
|---|-----|------|
| 1 | 空容器 front/back/top/pop/[] | 先 empty() |
| 2 | x = st.pop() 编译不过 | 先 top()/front() 再 pop() |
| 3 | erase/insert 直接写数字 | 必须 v.begin()+i |
| 4 | vector 单用 remove 没删 | 套 v.erase(remove(...), v.end()) |
| 5 | list 也套 erase-remove | list.remove 成员函数真删 |
| 6 | m[k] 判存在 → 插入污染 | count / find |
| 7 | multiset erase(x) 删光 | 删一个用 erase(find(x)) |
| 8 | find 失败和 -1 比 | 和 end() / string::npos 比 |
| 9 | npos+1 回绕成 0 | 做算术前先判 npos |
| 10 | v.size()-1 空时是巨数 | 先判空 |
| 11 | list 用 std::sort / lt[i] / it+n | lt.sort() / 不支持 / 只能 ++ -- |
| 12 | set/map 用全局 lower_bound | 用成员版 O(log n) |
| 13 | BFS 出队才标记 | 入队时标记 |
| 14 | reserve 后就 v[i] | reserve 不改 size，v[i] 仍 UB |
| 15 | transform 目标没开空间 | 先 resize |
| 16 | sort 的 cmp 写 a<=b | 相等必须返回 false（严格弱序） |
| 17 | 范围 for 大对象不加 & | const auto &x |
| 18 | 传容器参数不加 & | void f(vector<int>&) |
| 19 | substr 第二参写成结束下标 | 是长度 |
| 20 | vector v{5} 当成 5 个元素 | 花括号=列表，圆括号=个数+值 |

---

## 七、待补知识点清单（本手册未覆盖或仅补充区提及，建议另行整理）

| 缺失知识点 | 一句话补全 | 优先级 |
|-----------|-----------|--------|
| priority_queue | 默认大根堆（less）；小根堆 `priority_queue<int, vector<int>, greater<int>>`；只有 push/top/pop | P0 |
| unordered_map / unordered_set | 哈希表，平均 O(1) 最坏 O(n)；无序、无 lower/upper_bound；unordered_map 有 []，unordered_multimap 没有 | P0 |
| sort 完整版 | 内省排序（快排+堆排+插排），不稳定；要稳定用 stable_sort；cmp 必须严格弱序 | P0 |
| stringstream | 按空白切分单词、字符串与数值互转（scanf/printf 之外的 C++ 路线） | P1 |
| 迭代器适配器 | `back_inserter`：transform 免预开空间；反向迭代器 rbegin/rend | P1 |
| \<numeric\> | accumulate（求和，注意初值类型）、iota（填递增序列） | P1 |
| bitset | 定长位集合，位运算整体加速；状压与筛法的省内存替代 | P2 |

---

## 八、口诀集（一秒回忆）

1. **起点 + 长度**——substr / erase / replace 的数字参数都是这个模式。
2. **从哪开始、删几个、拿什么填**——replace 三参数。
3. **先取后弹**——stack/queue 都是 top/front 取值、pop 删除，pop 不返回值。
4. **内挤外删**——erase-remove：remove 管挤，erase 管删。
5. **判存在用 count/find，不用 []**——map 的 [] 会插入。
6. **erase(值) 删光，erase(迭代器) 删一个**——multiset/multimap 生死之差。
7. **入队即标记**——BFS 每个点只进队一次。
8. **下标前加 begin()+**——insert/erase 只收迭代器。
9. **存下标不存值**——滑动窗口最值要判「队首是否滑出窗口」，存值算不出位置。
10. **想按谁排序就把谁放 first**——pair 自带字典序，省写 cmp。

---

## 自测清单

- [ ] 能默写迭代器失效表与三档能力表
- [ ] 能默写 erase-remove、边遍历边删、BFS、单调栈、单调队列五个模板
- [ ] 易错 20 条逐条能说出「为什么是坑」
- [ ] 能不看资料讲清：pop 为什么返回 void、remove 为什么不能自己删、m[k] 为什么污染

## 错题登记

| 题号 | 错因 | 正解要点 |
|------|------|---------|
| （学完后填写） | | |

## 交付前自检清单

- [x] 框架树与素材目录逐条对账，无遗漏
- [x] 知识点一个不落且均标注 P0/P1/P2（含判定依据）；P0 ≤ 6 行、P1 2 至 3 行、P2 一行；每模板 ≤ 12 行；全篇 ≤ 600 行
- [x] 文本树为主，mermaid ≤ 1 个且配文字版
- [x] emoji 符合「限量」档位（仅 ❌✅⭐⚠️，≤ 15 个）
- [x] 易错总表编号可回查；口诀集每主题至少一条
- [x] 不确定处已显式标注；待补清单已列出
