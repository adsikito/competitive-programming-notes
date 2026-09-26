---
tags: [算法竞赛, STL]
优先级: P0
掌握状态: 未学
最后复习日期: （学完后填写，格式 YYYY-MM-DD；每次复习后回写）
来源: ① 课件 23 STL.pdf（pymupdf 提取，存 素材\STL\提取文本_23STL.txt）② 素材代码 4 组：string and vector code / list set map / stack queue list / algorithm（各组 Test002.cpp + mycode.cpp）③ 表达式括号匹配.cpp ④ 自编示例与断言程序（见附录 B-5）
生成日期: 2026-09-25
---

（掌握状态判定，写死：「已掌握」必须同时满足——(1) 六步叙事走完且每步验证动作通过；(2) 合卷手写核心代码 + g++ -std=c++17 编译通过 + 跑通⑥节边界数据集；(3) 能用大白话讲 5 分钟无卡壳。三者缺一，只可标「在学」。）

# STL

## 零、知识地图

```text
STL
├── 1. STL 总览与容器分类 —— 容器/迭代器/算法三大件与选型（前置：[[栈与队列]]）
├── 2. vector 深入 —— 动态数组、size 与 capacity、扩容均摊 O(1)（前置：知识点 1）
├── 3. set 与 map —— 自动排序的有序键，[[BST与AVL]] 的工业化封装（前置：知识点 1）
└── 4. 迭代器与竞赛 STL 速查 —— 前闭后开、sort/lower_bound/accumulate（前置：1-3，衔接 [[排序]]、[[二分]]）

学习顺序：1 → 2 → 3 → 4：先看清兵器库与选型方法，再攻出场率最高的 vector，然后是自动排序的关联容器，最后收拢到统一的访问方式与常用算法。
```

## 一、为什么需要它

先用你大概率碰过壁的方式做括号匹配（素材作业题 表达式括号匹配.cpp，以 @ 结尾）：手写栈要开 `char stk[256]`，push 写成 `stk[top++]`，pop 写成 `top--`，前后约 40 行，还得操心数组开多大、top 越没越界。素材这份代码改用 `stack<char>`，三行写完核心逻辑——但它在输入 `(()))@` 时弹了空栈（空栈上调 `stk.top()` 是未定义行为），实测程序崩溃退出（附录 B-5 登记 RE）。这个例子给出本篇两个任务：**把手写数据结构的时间省下来（用容器）；用不对照样 RE（要懂接口约定与复杂度）**。C 基线里你已手写过数组模拟栈/队列（[[栈与队列]]）；本篇把手艺升级成标准库：总览与选型（知识点 1）、vector 与扩容（知识点 2）、set/map（知识点 3）、迭代器与常用算法（知识点 4）。

## 二、知识点逐讲（每个知识点一节，共 4 节）

### 1. STL 总览与容器分类：三大件与兵器库

前置依赖：[[栈与队列]]（手写顺序栈/队列）、C 语言基础（数组、struct、[[函数]]）
后续衔接：[[#2. vector 深入：动态数组与扩容机制]]、[[#3. set 与 map：自动排序的有序键]]

**① 它解决什么问题**

STL（Standard Template Library，标准模板库）把常用数据结构及其算法实现了一遍，并做到**数据结构和算法的分离**（素材 23 STL.pdf「STL概述」页原话）。广义上分三类：**容器**（存数据的数据结构，如 vector、list、set）、**迭代器**（访问容器中对象的方法，如同指针）、**算法**（操作容器数据的模板函数，如 sort、find）。复杂度总账：vector 随机访问 $O(1)$、尾插均摊 $O(1)$；set/map 插入查找 $O(\log n)$；stack/queue 各操作 $O(1)$——选对容器，复杂度就定对了一大半。

**② 直觉理解**

模型级类比：**手写数据结构 = 自己打家具，STL = 家具租赁行**。自己打衣柜（手写栈）要量尺寸（开数组）、防塌（防越界）、坏了自己修；租赁行按目录取货（按接口用容器），目录写清承重与禁忌（复杂度与前置条件），但柜子塞超了照样塌——说明书必须读。用具体数字跑一遍：同一批数据 {5, 2, 8, 2} 装进 vector、set、map，三者行为完全不同（见④追踪表）——**选容器前先问自己要保序、要有序、还是要映射**。

**③ 原理与推导**

三大件如何协作（素材「STL基本组成」页）：算法不直接操作容器，而是拿一对迭代器指定范围——```text 容器 ──begin()/end()──> 迭代器（像指针一样走）──> 算法（sort/find，只认迭代器）```。文字版推导链：容器提供 begin 与 end；算法只在这对迭代器划定的 [begin, end) 区间内工作，于是同一个 sort 既能排 vector 也能排 C 数组；容器底层（vector 顺序表、list 双向链表、deque 循环队列、set 红黑树——素材原话）被封装，换实现不影响算法。

**设计动机**：为什么 stack、queue 叫"容器适配器"而不是独立容器？因为它们底层复用 deque，只是封掉一端的开口——栈只留顶端进出，队列只留一进一出；复用底层换来零成本的正确实现，代价是不允许遍历（素材 queue 页原话"队列不允许有遍历的行为"）。

**④ 代码演示**

块一「核心代码」（自编示例，演示同一批数据在三容器中的不同行为）：

```cpp
#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;                     // 等价 C：每个名字前加 std::
int main() {
    int a[4] = {5, 2, 8, 2};
    vector<int> vec; set<int> s; map<int, int> cnt;   // 等价 C：int vec[N],len=0; 无 set/map 现成对应
    for (int i = 0; i < 4; i++) {
        vec.push_back(a[i]);             // 尾插，等价 C：vec[len++] = a[i];
        s.insert(a[i]);                  // 插入即排序、重复值拒绝
        cnt[a[i]]++;                     // 键不存在时先创建再自增
    }
    cout << "vec: "; for (int x : vec) cout << x << " ";   // 范围 for，等价 C：for(i=0;i<len;i++)
    cout << "\nset: "; for (int x : s) cout << x << " ";
    cout << "\nmap: "; for (auto &p : cnt) cout << p.first << ":" << p.second << " ";
    return 0;
}
```

块二「执行追踪表」（数据 {5, 2, 8, 2}）：

| 步骤 | 当前元素 | 结构状态 | 动作 | 结果 |
|:---:|:---:|:---|:---|:---|
| 1 | 5 | 三容器均空 | 各自插入 5 | vec:[5] set:{5} map:{5->1} |
| 2 | 2 | vec:[5] | 各自插入 2 | vec:[5,2] set:{2,5} map:{2->1,5->1} |
| 3 | 8, 2 | vec:[5,2] | 插入 8；再插 2：vector 收下、set 拒绝重复、map 计数加 1 | vec:[5,2,8,2] set:{2,5,8} map:{2->2,5->1,8->1} |
| 4 | 遍历输出 | — | 三容器各输出一次 | vec 保序 5 2 8 2；set 有序去重 2 5 8；map 按键 2:2 5:1 8:1 |

块三「错误写法对照」（素材 表达式括号匹配.cpp 的空栈判定顺序错误，实测 RE）：

```diff
- else if (str[i] == ')') {
-     if (stk.top() == '(') stk.pop();        // 坑1：栈空时 top() 是未定义行为，输入 "(()))@" 实测崩溃退出（RE）
-     else if (stk.empty()) { cout << "NO"; }
- }
+ else if (str[i] == ')') {
+     if (stk.empty()) { cout << "NO"; return 0; }   // 修复：先判空，再谈弹出
+     stk.pop();
+ }
```

**⑤ 典型应用**

- 真题：洛谷 P1739 表达式括号匹配（素材作业题同源，题号真实）——`stack<char>` 收左括号，遇右括号弹出；空栈弹或最后非空都输出 NO。
- 真题：洛谷 P1449 后缀表达式（题号真实）——数字入栈，运算符弹两个数算完压回，`stack<long long>` 一把过。
- 迁移题：十进制转二进制（素材 stack queue list 组 test03 原题）。**建议先独立做，再对照题解**：除 2 取余得到低位到高位，恰好逆序，栈的先进后出把它正过来。

**⑥ 坑点与边界**

> **[!caution]**
> **【易错】** 空容器上调用 top()/front()/pop()。未定义行为，轻则答案错、重则 RE；任何弹出与取顶前先判 empty（素材括号匹配的实测崩溃即此类）。

> **[!caution]**
> **【易错】** 把 stack/queue 当序列容器遍历。它们没有 begin()/end()，需要遍历就用 vector 或 deque；选型口诀：随机访问 vector、两端进出 deque、自动排序去重 set、键值映射 map。

> [!example]-
> **边界数据集（先自己跑一遍，再展开对照）**
> 1. 空输入：n=0，不建容器不操作 → 程序空转结束，无输出不崩溃（预期：无输出）。
> 2. 单元素：插入 1 个 (5,1) → vec:[5] set:{5} map:{5->1}，三者输出各一行（预期：行为一致）。
> 3. 全相同：连插 5 个 2 → vec 5 个 2；set 仅 1 个 2；map {2->1} 或 {2->5} 视写法（预期：分清去重与计数）。
> 4. 严格递增：插 1..5 → set 升序不变，vector 保插入序（预期：两序恰好相同）。
> 5. 严格递减：插 5..1 → set 翻成升序 1..5，vector 保持递减（预期：排序发生在树不在插入序）。
> 6. 极值：n=1e6 查询的括号串 → stack 版 $O(n)$；若误写成"每次从头重扫"的 $O(n^2)$，1e12 次比较必超时（预期：选对容器与算法）。

回扣开场：现在你能解决开场那个括号匹配了——用的是知识点 1 的 stack 容器加"先判空再弹出"的接口纪律。下一节先攻最常用的 vector。

### 2. vector 深入：动态数组与扩容机制

前置依赖：[[#1. STL 总览与容器分类：三大件与兵器库]]、C 数组与指针（C 基础）
后续衔接：[[#3. set 与 map：自动排序的有序键]]、[[#4. 迭代器与竞赛 STL 速查：统一的访问与算法界面]]

**① 它解决什么问题**

静态数组必须编译期定长：n 上限估 1e5 开 `int a[200000]`，题目只来 10 个数就浪费，估小了越界 RE。**vector 是能自动增长的动态数组**（素材 vector 页：能够存放任意类型的动态数组），内存由标准库管理。关键性质：下标随机访问 $O(1)$；尾插均摊 $O(1)$；中间插删 $O(n)$。两个容易混淆的尺寸：**size 是已装元素个数，capacity 是已申请的槽位数**（素材：size 返回元素个数，capacity 返回当前所能容纳的最大元素值）。

**② 直觉理解**

模型级类比：**行李箱扩容**。size 是已装件数，capacity 是箱子容量：装满了就买一个两倍大的新箱子，旧物全部搬进去，旧箱子扔掉——这就是一次扩容；新箱子容量翻倍，接下来几次装箱都不用再换，**均摊下来每次装箱几乎是常数**。用具体数字跑一遍（g++ 实测，附录 B-5）：空 vector 连续 push_back 1 到 8，capacity 序列是 1, 2, 4, 8——每满一次翻一倍，而不是每次加一。

**③ 原理与推导**

扩容三步：申请更大的新内存（新容量约为旧的 2 倍，标准未写死，g++ 按 2 倍实测）→ 把旧元素逐个搬过去 → 释放旧内存。```text 旧块[1|2|4 槽] ──满──> 申请新块[1|2|4|8 槽] ──搬 4 个元素──> 释放旧块```。文字版推导链：第 k 次扩容要搬 k 次扩容前的全部元素；连插 n 个元素的总搬运量 $1+2+4+\cdots \le 2n$，均摊到每次插入是 $O(1)$——"均摊"的含义：单次可能贵，平摊起来便宜。

**设计动机**：为什么 size 与 capacity 分开记账？若每次插入都按需申请（capacity 恒等于 size），总搬运量 $1+2+\cdots+n = O(n^2)$；预留余量把总代价压到 $O(n)$。同理，已知规模时先 `v.resize(n)` 或 `v.reserve(n)` 一次到位，省掉全部中间扩容。

**④ 代码演示**

块一「核心代码」（自编示例，验证扩容序列；operator[] 与 at() 的差异见块三）：

```cpp
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> v;                        // 等价 C：int *a = NULL; int len = 0, cap = 0;
    for (int i = 1; i <= 8; i++) {
        v.push_back(i);                   // 满则换 2 倍大内存并整体搬迁
        cout << "size=" << v.size() << " cap=" << v.capacity() << "\n";
    }
    cout << v.front() << " " << v.back() << " " << v.at(7) << "\n";   // 1 8 8；[] 不查越界，at() 越界抛异常
    return 0;
}
```

块二「执行追踪表」（连插 1..8，g++ 实测）：

| 步骤 | 当前元素 | 结构状态 | 动作 | 结果 |
|:---:|:---:|:---|:---|:---|
| 1 | push_back(1) | size=0 cap=0 | 满，申请 cap=1 | size=1 cap=1 |
| 2 | push_back(2) | size=1 cap=1 | 满，申请 cap=2，搬 1 个 | size=2 cap=2 |
| 3 | push_back(3) | size=2 cap=2 | 满，申请 cap=4，搬 2 个 | size=3 cap=4 |
| 4 | push_back(4,5) | size=3 cap=4 | 4 未满直接装；5 满后扩 cap=8 搬 4 个 | size=5 cap=8 |
| 5 | push_back(6,7,8) | size=5 cap=8 | 未满，直接装 | size=8 cap=8 |

块三「错误写法对照」：

```diff
- for (auto it = v.begin(); it != v.end(); it++) { if (*it == 3) v.push_back(9); }   // 坑1：扩容后旧迭代器全失效，未定义行为（RE 或死循环）
+ int n = v.size();                    // 先记下规模，插入放到循环外
- int x = v[10];   // 坑2：size 为 5 时下标 10——operator[] 不检查越界，多半读出垃圾值（答案错）
+ int x = v.at(10);   // 调试期用 at()，越界抛 out_of_range，当场暴露问题
- vector<int> v2; copy(v1.begin(), v1.end(), v2.begin());   // 坑3：v2 空的，copy 无处可写（素材 test13 特意先 resize）
+ v2.resize(v1.size()); copy(v1.begin(), v1.end(), v2.begin());
```

**⑤ 典型应用**

- 真题：洛谷 P1177【模板】快速排序（题号真实）——`vector<int> v; while(n--) cin>>x, v.push_back(x);` 后接 `sort(v.begin(), v.end())`（见知识点 4），n 到 1e5 稳过；素材同组 test21（随机数求最大最小）展示"vector 当数组用"的最低门槛场景。
- 迁移题：读 n 个成绩，输出升序后的中位数（下标 n/2）。**建议先独立做，再对照题解**：push_back 装载、sort 排序、取 v[n/2]，三步是本节与知识点 4 的直接组装（自编示例）。

**⑥ 坑点与边界**

> **[!caution]**
> **【易错】** 遍历中 push_back 或 insert。扩容让全部迭代器与指针失效；先记规模再操作，或用下标循环加固定上界（④坑 1）。

> **[!caution]**
> **【易错】** resize 与 reserve 混用，以及中间频繁插删。resize(n) 造出 n 个元素（size=n，可直接下标）；reserve(n) 只留槽位（size 仍 0，下标即越界）。vector 中间插删是 $O(n)$ 整体搬移，频繁头插换 deque（素材 deque 页原话：支持高效插入删除容器的头部元素）。

> [!example]-
> **边界数据集（先自己跑一遍，再展开对照）**
> 1. 空输入：不插入任何元素 → size=0 cap=0，遍历零次（预期：无输出不崩）。
> 2. 单元素：push_back(7) → size=1 cap=1，v[0]=7、front()=back()=7（预期：一致）。
> 3. 全相同：插 5 个 2 → size=5，值全 2（预期：vector 不去重，与 set 对照记忆）。
> 4. 严格递增：插 1..8 → cap 序列 1,2,4,8（预期：与追踪表一致）。
> 5. 严格递减：插 8..1 → 同一 cap 序列，顺序无关（预期：扩容只看个数）。
> 6. 极值：n=1e6 次 push_back → 均摊 $O(n)$ 瞬间完成；若改成每次 insert 在头部，$O(n^2)$ = 1e12 次搬移必超时（预期：体会选型的复杂度后果）。

回扣开场：静态数组"开多大"的两难，被 size/capacity 双记账加翻倍扩容解决。现在你能用 vector 放心装载任意规模的数据了——接下来处理"要自动排序"的需求。

### 3. set 与 map：自动排序的有序键

前置依赖：[[#1. STL 总览与容器分类：三大件与兵器库]]、[[BST与AVL]]（二叉搜索树的有序性与 $O(\log n)$ 查找）
后续衔接：[[#4. 迭代器与竞赛 STL 速查：统一的访问与算法界面]]

**① 它解决什么问题**

"这 n 个数里 x 出现过没有？"——数组扫描 $O(n)$，n、m 都到 1e5 时 $10^{10}$ 次比较，必超时。**set/multiset 属于关联式容器，底层结构用二叉树实现，所有元素在插入时会自动被排序**（素材 set 页原话）；set 不允许重复，multiset 允许。map 是它的键值版：所有元素都是 pair，first 为键（索引）、second 为实值，按键自动排序，可以根据 key 快速找到 value。关键性质：insert/find/count/erase 均 $O(\log n)$；遍历得到按键升序的序列。

**② 直觉理解**

模型级类比：**图书馆按书号排架**。新书到手不用全书重排——顺着"书号在左还是右"走半棵树就找到该插的位置（[[BST与AVL]] 里的搜索路径）；找书同样只走半棵树。手写 AVL 要自己转旋转，set 是把调平这些脏活干完的**工业化版本**：你只管 insert，它保证树不歪、查询恒为 $O(\log n)$。用具体数字跑一遍（素材原例）：往空 set 依次插 10, 40, 30, 20, 30，遍历输出 10 20 30 40——第 5 个 30 因与树中已有 30 相同被拒绝。

**③ 原理与推导**

为什么插入与查找是 $O(\log n)$：底层是自平衡二叉搜索树（竞赛教材通识为红黑树，素材表述为"二叉树实现"，见 A-3 登记 1），n 个结点树高 $O(\log n)$，每次操作沿一条根到叶的路径走，比较次数等于路径长；1e5 个元素树高约 17 层，10 次操作共约 170 次比较，与暴力扫描的 $10^{10}$ 对比悬殊。

**设计动机**：为什么 set 不提供下标 v[i]？树结点在内存里不连续，"第 i 小"需要额外中序计数，与它"按值定位"的定位冲突；而 map 的 m[key] 是按键访问，语义完全不同。另一个动机：set 的 count 只能返回 0 或 1（素材原话），想计数用 multiset 或 map。

**④ 代码演示**

块一「核心代码」（取自素材 list set map 组 test02/test04 与 PDF set 页，改动：合并为单文件并加 C 等价注释）：

```cpp
#include <iostream>
#include <set>
#include <map>
#include <string>
using namespace std;
int main() {
    set<int> s;
    s.insert(20); s.insert(10); s.insert(50);       // 素材 test02 数据
    s.insert(30); s.insert(40); s.insert(20);       // 重复的 20 被拒绝
    for (int x : s) cout << x << " ";               // 10 20 30 40 50（插入即升序）
    cout << "\n" << s.count(20) << "\n";            // 1：set 的 count 只能 0 或 1
    map<string, int> score;                          // 等价 C：两个平行数组 + 手写查找
    score["XiaoMing"] = 50;                          // 键不存在则创建，存在则覆盖
    cout << score["XiaoMing"] << "\n";               // 50：按键 O(log n) 取值
    if (score.find("Nobody") == score.end())         // 查不存在用 find，别用 []
        cout << "Nobody not found\n";
    return 0;
}
```

块二「执行追踪表」（set 依次插入 10, 40, 30, 20, 30）：

| 步骤 | 当前元素 | 结构状态 | 动作 | 结果 |
|:---:|:---:|:---|:---|:---|
| 1 | insert(10) | 空树 | 成为根 | {10} |
| 2 | insert(40), insert(30) | {10} | 40>10 进右子树；30 走 10右、40左 | {10,30,40} |
| 3 | insert(20) | {10,30,40} | 20>10 右，20<40 左，20<30 左 | {10,20,30,40} |
| 4 | insert(30) | {10,20,30,40} | 与已有 30 相同 | 拒绝，size 仍 4 |

块三「错误写法对照」：

```diff
- if (score["Nobody"] > 0) { ... }        // 坑1：[] 查不存在的键会插入 (键, 0)，size 虚增——统计类题直接 WA（实测附录 B-5）
+ auto it = score.find("Nobody");
+ if (it != score.end()) { ... }          // find 只查不插，找不到返回 end()
- set<int> s = {1,2,2,3}; int c = s.count(2);   // 坑2：set 去重，count 恒 ≤1，按次数统计必错（答案错）
+ multiset<int> ms = {1,2,2,3}; int c = ms.count(2);   // 要计数用 multiset（素材 test08）
- for (auto it = s.begin(); it != s.end(); it++) { if (*it == 30) s.erase(it); }   // 坑3：erase 后 it 失效，继续 ++ 未定义（RE）
+ for (auto it = s.begin(); it != s.end(); ) { it = (*it == 30) ? s.erase(it) : next(it); }   // erase 返回下一个有效迭代器
```

**⑤ 典型应用**

- 真题：洛谷 P3370【模板】字符串哈希（题号真实）——n 个字符串求去重个数：`set<string> s; for(...) s.insert(t); cout << s.size();`，$O(n \log n)$，一行核心。
- 素材应用：multimap 一键多值（list set map 组，"XiaoMing" 对 50/55/60）——一个学生多门成绩的映射，multimap 允许重复键，find 返回第一个匹配。
- 迁移题：输入 n 个整数，输出去重后的个数与升序结果。**建议先独立做，再对照题解**：全部 insert 进 set 后遍历输出，size 即个数——去重与排序被 set 一次包办（自编示例）。

**⑥ 坑点与边界**

> **[!caution]**
> **【易错】** 用 map 的 [] 判断键是否存在。不存在时会创建默认值，容器被污染；查询一律 find 或 count（④坑 1）。

> **[!caution]**
> **【易错】** 遍历中 erase 后继续用旧迭代器。失效迭代器一走就 RE；用 erase 的返回值接续（④坑 3）。另外 set 的键只读：改键会破坏树的有序性，要改只能 erase 再 insert。

> [!example]-
> **边界数据集（先自己跑一遍，再展开对照）**
> 1. 空输入：n=0 → set 空，size()=0，遍历零次（预期：无输出不崩）。
> 2. 单元素：insert(42) → size=1，find(42) 命中，count(42)=1（预期：一致）。
> 3. 全相同：insert 5 次 7 → set size=1；multiset size=5，count(7)=5（预期：分清两个容器）。
> 4. 严格递增：插 1..5 → 树右斜，自平衡后查找仍 $O(\log n)$（预期：输出 1 2 3 4 5）。
> 5. 严格递减：插 5..1 → 同上反转（预期：输出 1 2 3 4 5，体会"与插入序无关"）。
> 6. 极值：n=1e6 次 find → 约 $10^6 \times 20$ 次比较瞬间完成；换数组线性扫描是 $10^{12}$ 次，必超时（预期：复杂度差距落到具体数字）。

回扣开场：暴力扫描 $10^{10}$ 次的"出现过没有"，被 $O(\log n)$ 的有序键容器收编。现在你能解决"去重、计数、按名查分"这一整类题了——下一节把所有容器共用的访问方式与常用算法一次讲完。

### 4. 迭代器与竞赛 STL 速查：统一的访问与算法界面

前置依赖：[[#1. STL 总览与容器分类：三大件与兵器库]]、[[#2. vector 深入：动态数组与扩容机制]]、[[#3. set 与 map：自动排序的有序键]]
后续衔接：[[排序]]（sort 的内部思想与手写版）、[[二分]]（lower_bound 的手写版与题面应用）

**① 它解决什么问题**

vector 用下标走，set 不能用下标走——每个容器各写一套遍历太累。**迭代器提供访问容器中对象的方法，就如同一个指针**（素材 STL基本组成页原话）：begin() 指向第一个元素，end() 指向最后一个元素的**下一个位置**，区间 [begin, end) 前闭后开。所有 STL 算法（sort、lower_bound、accumulate 等）都只认迭代器，同一套函数排遍一切容器与数组。关键性质：范围 for 是迭代器的语法糖；算法集中在 \<algorithm\> 与 \<numeric\> 两个头文件（素材原话）。

**② 直觉理解**

模型级类比：**书签**。迭代器就是夹在容器里的书签：`*it` 读当前页（解引用），`++it` 翻下一页，`it - v.begin()` 报告夹在第几页（仅 vector 等随机访问容器支持相减）；算法是只会用书签的读书机器——不关心书是精装（vector）还是活页（list），夹上书签就能干活。用具体数字跑一遍：v = {1,3,5,7,9}，lower_bound(v.begin(), v.end(), 6) 的书签依次跳到值 5（不够 6）、值 9（超了）、再收窄，最终停在值 7——第一个大于等于 6 的位置（完整过程见④追踪表）。

**③ 原理与推导**

为什么区间设计成前闭后开 [begin, end)：第一，空区间统一表示为 begin == end，不需要"end 是否合法"的特判；第二，循环条件 `it != end` 对所有容器成立，"最后一个元素"这种需要 end-1 的写法被绕开（list 根本做不了 end-1）。**设计动机**：算法为什么收迭代器不收容器？排序数组与排序 vector 在算法眼里是同一件事——"一段可以 ++ 与比较的区间"；收迭代器让 `sort(a, a+n)`（C 数组）与 `sort(v.begin(), v.end())`（vector）通用，这正是知识点 1"数据结构和算法的分离"落到接口上的样子。

**④ 代码演示**

块一「核心代码」（自编速查；用法与素材 algorithm 组 mycode.cpp 一致，完整版见源文件 mycode.cpp）：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>   // sort / lower_bound / binary_search
#include <numeric>     // accumulate
using namespace std;
int main() {
    vector<int> v = {9, 1, 7, 3, 5};                  // 等价 C：int v[5]={...};
    sort(v.begin(), v.end());                         // 升序 O(n log n)，等价 C：qsort + 手写比较器；降序加 greater<int>()（素材 test09）
    bool has = binary_search(v.begin(), v.end(), 7);  // 前提：区间已排序，返回 bool
    auto it = lower_bound(v.begin(), v.end(), 6);     // 第一个 >= 6 的迭代器
    int pos = it - v.begin();                         // 迭代器相减 = 下标，等价 C：指针相减
    long long sum = accumulate(v.begin(), v.end(), 0LL);  // 初值 0LL：决定按 long long 累加
    cout << pos << " " << has << " " << sum << "\n";  // 3 1 25
    return 0;                                         // reverse/count 见素材 mycode.cpp test12/test07
}
```

块二「执行追踪表」（lower_bound 找 6，v 已排序为 {1,3,5,7,9}，二分区间 [lo, hi)）：

| 步骤 | 当前元素 | 结构状态 | 动作 | 结果 |
|:---:|:---:|:---|:---|:---|
| 1 | 区间 [0,5) | {1,3,5,7,9} | mid=2，值 5 < 6，答案在右半 | lo=3 |
| 2 | 区间 [3,5) | {7,9} | mid=4，值 9 >= 6，答案在左半含自身 | hi=4 |
| 3 | 区间 [3,4) | {7} | mid=3，值 7 >= 6 | hi=3 |
| 4 | 区间 [3,3) | 空 | lo==hi，停止 | 返回下标 3，值 7 |

块三「错误写法对照」：

```diff
- auto it = lower_bound(v.begin(), v.end(), 6);   // 坑1：v={9,1,7,3,5} 未排序，lower_bound 前提崩塌，结果无意义（答案错）
+ sort(v.begin(), v.end()); auto it = lower_bound(v.begin(), v.end(), 6);   // 先 sort 再二分
- int s = accumulate(v.begin(), v.end(), 0);      // 坑2：初值 0 决定按 int 累加，1e5 个 1e9 相加溢出（答案错）
+ long long s = accumulate(v.begin(), v.end(), 0LL);   // 初值类型决定累加类型（实测附录 B-5）
- bool cmp(int a, int b) { return a <= b; }        // 坑3：比较器写 <=，相等元素"互为更小"，sort 内部越界（RE）
+ bool cmp(int a, int b) { return a > b; }         // 严格弱序：相等时必须返回 false
```

**⑤ 典型应用**

- 真题：洛谷 P1102 A-B 数对（题号真实）——统计数对 $A-B=C$：排序后对每个 a 查 $a-C$ 的个数，`upper_bound - lower_bound` 一次得出，总复杂度 $O(n \log n)$；暴力二重循环 $O(n^2)$ 在 n=2e5 时超时。
- 真题：洛谷 P1177【模板】快速排序（知识点 2⑤ 已引用）——本节 sort 就是它的最后一块拼图。
- 迁移题：有序数组求大于等于 x 的最小值，不存在输出 -1。**建议先独立做，再对照题解**：lower_bound 得 it，`it == v.end()` 时输出 -1，否则输出 `*it`——正是 [[二分]] 手写模板的库函数版（自编示例）。

**⑥ 坑点与边界**

> **[!caution]**
> **【易错】** 对未排序区间调 lower_bound 或 binary_search。前提崩塌，返回值无意义；先 sort 再二分（④坑 1）。

> **[!caution]**
> **【易错】** accumulate 初值写 0，int 溢出静悄悄；求和先想 long long，初值写 0LL（④坑 2）。另注意 end 不指向有效元素——`*v.end()` 是越界，"最后一个元素"用 v.back()。

> [!example]-
> **边界数据集（先自己跑一遍，再展开对照）**
> 1. 空输入：sort/lower_bound 作用于空 vector → begin==end，零次比较（预期：无输出不崩）。
> 2. 单元素：{5} 中 lower_bound(5) → 下标 0；lower_bound(6) → end()（预期：判 end 再解引用）。
> 3. 全相同：{2,2,2} 中 lower_bound(2) → 下标 0，upper_bound(2) → end()，两者相减 = 3 = 个数（预期：掌握"个数 = 两边界之差"）。
> 4. 严格递增：{1,3,5,7,9} 查 6 → 下标 3（预期：与追踪表一致）。
> 5. 严格递减：不适用：lower_bound 要求升序区间；递减区间需先 reverse 或传比较器（预期：理解前提）。
> 6. 极值：1e5 个 1e9 求和 → 初值 0 的 int 版溢出为负数，0LL 版得 1e14（预期：溢出可测，附录 B-5 已验证）。

回扣开场：手写栈的 40 行与 $O(n^2)$ 的扫描，被容器、迭代器、算法三件套替换成十几行复杂度正确的代码。现在你能解决开场那个括号匹配，也能在 1e5 规模下安全地排序、去重、二分了。

## 三、全篇坑点总表

| # | 坑 | 正解 |
|---|-----|------|
| 1 | 空容器上 top()/front()/pop() | 先判 empty 再操作（知识点 1④） |
| 2 | 遍历中 push_back/insert；resize 与 reserve 混用 | 先记规模再插入；resize 造元素、reserve 只留槽位 |
| 3 | map 用 [] 判存在 | find/count；[] 会插入默认值 |
| 4 | set.count 当计数用 | set 恒 ≤1；计数用 multiset 或 map |
| 5 | 遍历中 erase 后继续 ++ | 用 erase 返回值接续 |
| 6 | lower_bound 前忘排序 | 先 sort，前提是升序区间 |
| 7 | accumulate 初值写 0 | 写 0LL，初值类型决定累加类型 |
| 8 | 比较器写 <= | 严格弱序：相等返回 false |

## 四、总结与自测

### 核心内容（一页纸速览）

- **STL 三大件**：容器存数据、迭代器访问、算法操作；数据结构与算法分离，复杂度随容器选型而定（素材 23 STL.pdf）。选型：随机访问 vector；两端进出 deque；自动排序去重 set；键值映射 map；先进后出/先出选 stack/queue（适配器，不可遍历）。
- **vector**：动态数组；size=已装个数，capacity=已申请槽位；扩容约 2 倍翻新，总搬运 $\le 2n$，尾插均摊 $O(1)$。
- **set/map**：底层自平衡二叉搜索树，插入查找 $O(\log n)$，插入即升序；set 去重、multiset 可重；map 按键索引 pair。
- **迭代器与速查算法**：区间 [begin, end) 前闭后开，范围 for 是语法糖；sort（greater 降序）、lower_bound/upper_bound（升序前提）、binary_search、accumulate（初值定类型）、reverse、count；个数 = upper_bound - lower_bound。

### 自测清单

- [ ] 能画出同一批数据在 vector/set/map 中的三种结果并解释原因
- [ ] 能手推连插 1..8 的 size/capacity 序列并算出均摊 O(1) 的求和依据
- [ ] 能默写 set 插入 {10,40,30,20,30} 的树形路径与最终输出
- [ ] 能说清 map 的 [] 与 find 的差异及各自后果
- [ ] 能默写 sort+lower_bound+accumulate 速查并解释 0LL 的作用、手推 lower_bound 找 6 的四步追踪表

### 错题登记

| 题号 | 错因 | 正解要点 |
|------|------|---------|
| （学完后填写） | | |

## 五、语法糖对照表

| 语法 | 等价 C 写法 | 一句话用途 |
|------|------------|-----------|
| `vector<int> v; v.push_back(x);` | `int a[N]; a[len++] = x;` | 可增长数组 |
| `v.size()` / `v.capacity()` | 自记 `len` / `cap` 两个变量 | 个数与槽位分开记账 |
| `set<int> s; s.insert(x);` / `map<K,V> m; m[k]=v;` | 手写有序数组 + 二分插入 / 平行数组 + 手写查找 | 自动排序去重 / 按键索引 |
| `for (auto x : v) {...}` / `auto it = v.begin();` | `for (i = 0; i < len; i++)` 用 `v[i]` / `int *p = a;` | 遍历语法糖 / 免写冗长类型 |
| `cin >> x;` / `cout << x << "\n";` | `scanf("%d",&x);` / `printf("%d\n",x);` | 流式读写 |
| `sort(v.begin(), v.end());` | `qsort(a, n, sizeof(int), cmp);` | 排序免比较器 |
| `using namespace std;` | 每个标识符前加 `std::` | 免前缀 |

---
## 附录（供验收，正文之外，不影响阅读）

### 附录 A　源文件覆盖对账

#### A-1 提取表

| 源文件 | 提取方式 | 完整性 |
| --- | --- | --- |
| 23 STL.pdf | pymupdf 全文提取，存 提取文本_23STL.txt（2237 行） | 基本完整：三大件与全套容器 API；文本止于 accumulate 小节（附录 B-3 登记），algorithm 代码组已覆盖同类 API |
| string and vector code 组 | mycode.cpp + Test002.cpp 直读 | 完整：string 初始化/substr/insert/erase/replace；vector 声明/遍历/增删/swap；随机数求最大最小（test21） |
| list set map 组 | mycode.cpp + Test002.cpp 直读 | 完整：set 去重遍历、multiset count 与 lower/upper_bound、pair/make_pair、map 四种插入、multimap 一键多值 |
| stack queue list 组 | mycode.cpp + Test002.cpp 直读 | 完整：stack 进制转换（test03/04）、queue 扑克出牌（test07）、deque VIP 插队（test14）、list 自定义排序（test20） |
| algorithm 组 | mycode.cpp + Test002.cpp 直读 | 完整：for_each/transform、find/count 族、sort/merge/reverse、copy/replace、accumulate/fill、集合运算、约瑟夫出圈（test22） |
| 表达式括号匹配.cpp | 直读（41 行） | 完整；含空栈判定顺序错误（知识点 1④ 实测复现） |

#### A-2 知识点总清单（4 对 4）

| 序号 | 知识点 | 对应源文件 | 优先级 |
|------|--------|-----------|--------|
| 1 | STL 总览与容器分类 | 23 STL.pdf（概述/基本组成/stack/queue 页）+ 表达式括号匹配.cpp | P0 |
| 2 | vector 深入与扩容机制 | 23 STL.pdf（vector 页）+ string and vector code 组（test15-test21） | P0 |
| 3 | set 与 map 有序键 | 23 STL.pdf（set/map/multimap 页）+ list set map 组（test01-test17） | P0 |
| 4 | 迭代器与竞赛 STL 速查 | 23 STL.pdf（迭代器/常用算法页）+ algorithm 组（test03-test17） | P0 |

依赖关系：1 是 2/3 的选型基础；2 提供装载载体（sort 作用于 vector）；3 提供有序性（lower_bound 的容器版）；4 统一前三者的访问界面并收拢算法。素材中 string/deque/list 的 API 细节并入知识点 1 的选型叙述，不单独成节（去重合并）。

#### A-3 冲突与约定差异登记（3 项）

| 何处冲突 | 采信哪方 | 理由 |
| --- | --- | --- |
| set/map 底层：素材写"用二叉树实现"，竞赛教材通识为"红黑树" | 正文写"自平衡二叉搜索树（通识为红黑树）" | 素材未指明树种类别；红黑树是公认结论，[[BST与AVL]] 已铺垫平衡树，此处不展开旋转 |
| 素材 test19 的 list 比较器 `int cmp(...)` 返回 `a > b` | 正文统一用 `bool cmp(...)` | 返回 int 非标准写法，g++ 接受但换编译器有告警风险；逻辑语义一致（降序） |
| 素材 stack 进制转换（test04）用 switch 枚举十六进制字符 | 迁移题取其二进制版（test03） | 两版等价；二进制版更能突出栈逆序本质，完整版见源文件 |

### 附录 B　假设与缺口登记

- B-1 假设清单：学习者已会 C 数组、指针、struct、函数与手写栈/队列（[[栈与队列]]）；未学过任何 STL 容器、迭代器、范围 for、auto。C++ 特性首现处均附 C 等价注释，篇末汇总对照表。
- B-2 资料缺口：素材未讲 vector 扩容的均摊复杂度推导（只给 API），知识点 2③ 的翻倍与 $\le 2n$ 搬运推导按通识补讲；素材未讲严格弱序比较器，知识点 4⑥ 按通识补讲。
- B-3 读取缺口：提取文本止于 accumulate 小节，PDF 后续 fill 等小节未入文本层；因 algorithm 代码组已覆盖同类 API，未再渲染 PNG 补提。真题题号（P1739/P1449/P1177/P3370/P1102）为通识补充，均真实存在。
- B-4 知识点 1-4 的④核心代码为自编示例（含 C 等价注释，假设学习者未学过任何 STL）；API 用法与素材源码一致，差异处已在 A-3 登记。
- B-5 编译验证记录（g++ -std=c++17，目录 Temp\batch89_verify）：① 素材 4 组 mycode.cpp 与 表达式括号匹配.cpp 语法检查全部 exit=0；② 断言程序 verify_stl.cpp **22 PASS / 0 FAIL**：括号匹配修正版 5 例（"(()))@"、"(()@"、")(" 为 NO，"(()()())@"、"(())@" 为 YES）；vector 扩容 cap 序列 1,2,4,8；set 去重排序输出 1 2 3 4 5 且 count(3)==1；multiset count(4)==3 且 lower/upper_bound(8)==9；map [] 默认插入 (7,0)、m[4]=40、m[1]=66 覆盖；sort 升序/降序；lower_bound(6) 于 {1,2,5,7,9} 得下标 3 值 7；binary_search(5) 为真；accumulate 0LL 得 4e9（int 初值溢出对照）；reverse/count/find_if。③ 断言程序曾把 "(()()())@" 误标为预期 NO（实际配对成立），修正测试预期后全过——教训：写断言先核对测试数据本身。

### 附录 C　交付前自检清单

- [x] 附录 A 有逐份提取表；总清单 4 条 = 正文知识点 4 节，编号一一对应
- [x] 每个知识点六步齐全，以问题开场、以回扣收尾，无「只有定义没有推导」；无未解释的新术语；无「显然 / 易得 / 略」；全文无 emoji
- [x] callout 声明行独占一行、单块单主标签；标题不跳级；表格不超过 6 列
- [x] 代码均为 C++17 可编译（实测 exit=0），例子用具体数字算过；迁移题标注出处或「自编」；真题题号真实
- [x] frontmatter 六项齐全；「零、知识地图」文本树在篇首；每个知识点有「前置依赖 / 后续衔接」两字段
- [x] ④节为「代码演示」三块：核心代码 + 执行追踪表（4 张）+ 错误写法对照（4 组）
- [x] ⑥节末尾有边界数据集（六类折叠 callout，含极值）；C++ 特性首现处有 C 等价注释，篇末有《语法糖对照表》
- [x] mermaid 0 个（文本图 + 文字版推导链）；性质融入正文（复杂度总账在各①节）；每个知识点含设计动机回答；工程痕迹全部在附录（对账 / 假设 / 自检），正文无验收类内容
