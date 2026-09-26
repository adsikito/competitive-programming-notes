---
tags: [算法竞赛, STL, 复习回顾]
优先级: P0
掌握状态: 未学
最后复习日期: （每次复习后回写，格式 YYYY-MM-DD）
来源: STL.md
生成日期: 2026-09-26
---

# STL · 复习回顾版

> 压缩口径：由学习版 [[STL]] 直接压缩，知识点清单 4 对 4（编号/顺序/名称/优先级一致）；结论均可在学习版对应卡片溯源。

## 零、知识地图

```text
STL
├── 1. STL 总览与容器分类 —— 容器/迭代器/算法三大件与选型（前置：[[栈与队列]]）
├── 2. vector 深入 —— 动态数组、size 与 capacity、扩容均摊 O(1)（前置：知识点 1）
├── 3. set 与 map —— 自动排序的有序键，[[BST与AVL]] 的工业化封装（前置：知识点 1）
└── 4. 迭代器与竞赛 STL 速查 —— 前闭后开、sort/lower_bound/accumulate（前置：1-3，衔接 [[排序]]、[[二分]]）

学习顺序：1 → 2 → 3 → 4：先看清兵器库与选型方法，再攻出场率最高的 vector，然后是自动排序的关联容器，最后收拢到统一的访问方式与常用算法。
```

## 一、知识点逐卡（4 对 4，与学习版同编号同顺序）

### 【P0】1. STL 总览与容器分类：三大件与兵器库

前置依赖：[[STL]]｜后续衔接：[[STL#2. vector 深入：动态数组与扩容机制]]、[[STL#3. set 与 map：自动排序的有序键]]
关联错题：暂无

**① 结论与识别信号**：STL 三大件——容器（存数据）、迭代器（访问，如同指针）、算法（操作容器的模板函数），做到数据结构与算法分离；选对容器，复杂度就定对了一大半（vector 随机访问 O(1)、尾插均摊 O(1)；set/map 插入查找 O(log n)；stack/queue 各操作 O(1)）。识别信号：看到"个数不定往尾装"就想到 vector，"自动去重/有序"想到 set，"按名查值"想到 map，"先进后出/先出"想到 stack/queue，"要遍历"就排除 stack/queue（它们没有 begin()/end()）。

**② 数据推演结果**：同一批数据 {5, 2, 8, 2} 装三容器：vector 保序输出 5 2 8 2；set 有序去重输出 2 5 8；map 按键计数输出 2:2 5:1 8:1。选容器前先问自己：要保序、要有序、还是要映射。

**③ 核心结论与推导链**：推导链——容器提供 begin()/end() → 算法只在这对迭代器划定的 [begin, end) 区间内工作 → 同一个 sort 既能排 vector 也能排 C 数组 → 容器底层（vector 顺序表、list 双向链表、deque 循环队列、set 红黑树）被封装，换实现不影响算法。stack/queue 是"容器适配器"：底层复用 deque、只留一端开口，换来零成本的正确实现，代价是不允许遍历。

**④ 代码与追踪**：

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

执行追踪表（数据 {5, 2, 8, 2}）：

| 步骤 | 当前元素 | 结构状态 | 动作 | 结果 |
|:---:|:---:|:---|:---|:---|
| 1 | 5 | 三容器均空 | 各自插入 5 | vec:[5] set:{5} map:{5->1} |
| 2 | 2 | vec:[5] | 各自插入 2 | vec:[5,2] set:{2,5} map:{2->1,5->1} |
| 3 | 8, 2 | vec:[5,2] | 插入 8；再插 2：vector 收下、set 拒绝重复、map 计数加 1 | vec:[5,2,8,2] set:{2,5,8} map:{2->2,5->1,8->1} |
| 4 | 遍历输出 | — | 三容器各输出一次 | vec 保序 5 2 8 2；set 有序去重 2 5 8；map 按键 2:2 5:1 8:1 |

**⑤ 真题索引**：

- 洛谷 P1739 表达式括号匹配：`stack<char>` 收左括号，遇右括号弹出；空栈弹或最后非空都输出 NO。
- 洛谷 P1449 后缀表达式：数字入栈，运算符弹两个数算完压回，`stack<long long>` 一把过。
- 迁移题（素材 stack queue list 组 test03）：十进制转二进制——除 2 取余得低位到高位恰好逆序，栈的先进后出把它正过来。

**⑥ 坑点与边界数据集**：

> [!caution]
> **【易错】** 空容器上调用 top()/front()/pop()——未定义行为，轻则答案错、重则 RE。
> 错误写法：`if (stk.top() == '(') stk.pop();`（输入 "(()))@" 实测崩溃退出）；正确写法：`if (stk.empty()) { cout << "NO"; return 0; } stk.pop();`——任何弹出与取顶前先判 empty。

> [!caution]
> **【易错】** 把 stack/queue 当序列容器遍历——它们没有 begin()/end()，需要遍历就用 vector 或 deque。

> [!example]-
> **边界数据集（先自己跑一遍，再展开对照）**
> 1. 空输入：n=0，不建容器不操作 → 程序空转结束，无输出不崩溃（预期：无输出）。
> 2. 单元素：插入 1 个 (5,1) → vec:[5] set:{5} map:{5->1}，三者输出各一行（预期：行为一致）。
> 3. 全相同：连插 5 个 2 → vec 5 个 2；set 仅 1 个 2；map {2->1} 或 {2->5} 视写法（预期：分清去重与计数）。
> 4. 严格递增：插 1..5 → set 升序不变，vector 保插入序（预期：两序恰好相同）。
> 5. 严格递减：插 5..1 → set 翻成升序 1..5，vector 保持递减（预期：排序发生在树不在插入序）。
> 6. 极值：n=1e6 查询的括号串 → stack 版 O(n)；若误写成"每次从头重扫"的 O(n^2)，1e12 次比较必超时（预期：选对容器与算法）。

### 【P0】2. vector 深入：动态数组与扩容机制

前置依赖：[[STL]]｜后续衔接：[[STL#3. set 与 map：自动排序的有序键]]、[[STL#4. 迭代器与竞赛 STL 速查：统一的访问与算法界面]]
关联错题：暂无

**① 结论与识别信号**：vector 是能自动增长的动态数组——下标随机访问 O(1)、尾插均摊 O(1)、中间插删 O(n)；size 是已装元素个数，capacity 是已申请槽位数，两个分开记账。识别信号：看到"n 不知道多大、装到末尾、还要按下标取"就想到 vector；看到"已知规模"就先 resize/reserve 一次到位。

**② 数据推演结果**：空 vector 连续 push_back 1 到 8，capacity 序列为 1, 2, 4, 8（g++ 实测）——每满一次翻一倍，不是每次加一。

**③ 核心结论与推导链**：推导链——第 k 次扩容要搬此前全部元素 → 连插 n 个的总搬运量 1+2+4+…≤2n → 均摊到每次插入是 O(1)（"均摊"含义：单次可能贵，平摊起来便宜）。推论：若每次插入都按需申请（capacity 恒等于 size），总代价 O(n^2)；已知规模先 `v.resize(n)` 或 `v.reserve(n)` 可省掉全部中间扩容。

**④ 代码与追踪**：

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

执行追踪表（连插 1..8，g++ 实测）：

| 步骤 | 当前元素 | 结构状态 | 动作 | 结果 |
|:---:|:---:|:---|:---|:---|
| 1 | push_back(1) | size=0 cap=0 | 满，申请 cap=1 | size=1 cap=1 |
| 2 | push_back(2) | size=1 cap=1 | 满，申请 cap=2，搬 1 个 | size=2 cap=2 |
| 3 | push_back(3) | size=2 cap=2 | 满，申请 cap=4，搬 2 个 | size=3 cap=4 |
| 4 | push_back(4,5) | size=3 cap=4 | 4 未满直接装；5 满后扩 cap=8 搬 4 个 | size=5 cap=8 |
| 5 | push_back(6,7,8) | size=5 cap=8 | 未满，直接装 | size=8 cap=8 |

**⑤ 真题索引**：

- 洛谷 P1177【模板】快速排序：`vector<int> v; while(n--) cin>>x, v.push_back(x);` 后接 `sort(v.begin(), v.end())`，n 到 1e5 稳过。
- 迁移题（自编）：读 n 个成绩，输出升序后的中位数——push_back 装载、sort 排序、取 `v[n/2]`，三步直接组装。

**⑥ 坑点与边界数据集**：

> [!caution]
> **【易错】** 遍历中 push_back 或 insert——扩容让全部迭代器与指针失效，未定义行为（RE 或死循环）。
> 错误写法：`for (auto it = v.begin(); it != v.end(); it++) { if (*it == 3) v.push_back(9); }`；正确写法：`int n = v.size();` 先记下规模，插入放到循环外，或用下标循环加固定上界。

> [!caution]
> **【易错】** operator[] 与 at() 的差异——`int x = v[10];` 在 size 为 5 时是未定义行为，多半读出垃圾值（答案错）；调试期用 `v.at(10)`，越界抛 out_of_range 当场暴露。

> [!caution]
> **【易错】** resize 与 reserve 混用，以及对空 vector copy——resize(n) 造出 n 个元素（size=n，可直接下标），reserve(n) 只留槽位（size 仍 0，下标即越界）；`copy(v1.begin(), v1.end(), v2.begin());` 在 v2 为空时无处可写，须先 `v2.resize(v1.size());`。另：vector 中间插删是 O(n) 整体搬移，频繁头插换 deque。

> [!example]-
> **边界数据集（先自己跑一遍，再展开对照）**
> 1. 空输入：不插入任何元素 → size=0 cap=0，遍历零次（预期：无输出不崩）。
> 2. 单元素：push_back(7) → size=1 cap=1，v[0]=7、front()=back()=7（预期：一致）。
> 3. 全相同：插 5 个 2 → size=5，值全 2（预期：vector 不去重，与 set 对照记忆）。
> 4. 严格递增：插 1..8 → cap 序列 1,2,4,8（预期：与追踪表一致）。
> 5. 严格递减：插 8..1 → 同一 cap 序列，顺序无关（预期：扩容只看个数）。
> 6. 极值：n=1e6 次 push_back → 均摊 O(n) 瞬间完成；若改成每次 insert 在头部，O(n^2) = 1e12 次搬移必超时（预期：体会选型的复杂度后果）。

### 【P0】3. set 与 map：自动排序的有序键

前置依赖：[[STL]]、[[BST与AVL]]｜后续衔接：[[STL#4. 迭代器与竞赛 STL 速查：统一的访问与算法界面]]
关联错题：暂无

**① 结论与识别信号**：set/multiset 底层用二叉树实现（自平衡二叉搜索树，通识为红黑树），所有元素插入时自动排序，insert/find/count/erase 均 O(log n)；set 不允许重复、multiset 允许；map 是键值版——元素都是 pair，first 为键、second 为实值，按键自动排序。识别信号：看到"x 出现过没有""去重个数""按名字查成绩"就想到 set/map，而不是数组扫描。

**② 数据推演结果**：空 set 依次插 10, 40, 30, 20, 30 → 遍历输出 10 20 30 40，第 5 个 30 因与树中已有 30 相同被拒绝（size 为 4）。

**③ 核心结论与推导链**：推导链——n 个结点的自平衡树高 O(log n) → 每次操作沿一条根到叶路径走，比较次数等于路径长 → 1e5 个元素树高约 17 层，10 次操作约 170 次比较，对比暴力扫描的 10^10 次悬殊。两个语义要点：set 不提供下标 v[i]（树结点在内存不连续，"第 i 小"与它"按值定位"的定位冲突）；set 的 count 只能返回 0 或 1，想计数用 multiset 或 map。

**④ 代码与追踪**：

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

执行追踪表（set 依次插入 10, 40, 30, 20, 30）：

| 步骤 | 当前元素 | 结构状态 | 动作 | 结果 |
|:---:|:---:|:---|:---|:---|
| 1 | insert(10) | 空树 | 成为根 | {10} |
| 2 | insert(40), insert(30) | {10} | 40>10 进右子树；30 走 10右、40左 | {10,30,40} |
| 3 | insert(20) | {10,30,40} | 20>10 右，20<40 左，20<30 左 | {10,20,30,40} |
| 4 | insert(30) | {10,20,30,40} | 与已有 30 相同 | 拒绝，size 仍 4 |

**⑤ 真题索引**：

- 洛谷 P3370【模板】字符串哈希：n 个字符串求去重个数——`set<string> s; for(...) s.insert(t); cout << s.size();`，O(n log n) 一行核心。
- 素材应用（list set map 组）：multimap 一键多值——一个学生多门成绩的映射，允许重复键，find 返回第一个匹配。
- 迁移题（自编）：输入 n 个整数，输出去重后的个数与升序结果——全部 insert 进 set 后遍历输出，size 即个数，去重与排序一次包办。

**⑥ 坑点与边界数据集**：

> [!caution]
> **【易错】** 用 map 的 [] 判断键是否存在——不存在时会创建 (键, 0) 默认值，容器被污染，统计类题直接 WA。
> 错误写法：`if (score["Nobody"] > 0) { ... }`；正确写法：`auto it = score.find("Nobody"); if (it != score.end()) { ... }`——find 只查不插，找不到返回 end()。查询一律 find 或 count。

> [!caution]
> **【易错】** 把 set 的 count 当计数用——set 去重后 count 恒不超过 1，按次数统计必错。
> 错误写法：`set<int> s = {1,2,2,3}; int c = s.count(2);`；正确写法：`multiset<int> ms = {1,2,2,3}; int c = ms.count(2);`——要计数用 multiset 或 map。

> [!caution]
> **【易错】** 遍历中 erase 后继续用旧迭代器——失效迭代器一走就 RE；set 的键只读，改键会破坏树的有序性，要改只能 erase 再 insert。
> 错误写法：`for (auto it = s.begin(); it != s.end(); it++) { if (*it == 30) s.erase(it); }`；正确写法：`for (auto it = s.begin(); it != s.end(); ) { it = (*it == 30) ? s.erase(it) : next(it); }`——用 erase 的返回值接续。

> [!example]-
> **边界数据集（先自己跑一遍，再展开对照）**
> 1. 空输入：n=0 → set 空，size()=0，遍历零次（预期：无输出不崩）。
> 2. 单元素：insert(42) → size=1，find(42) 命中，count(42)=1（预期：一致）。
> 3. 全相同：insert 5 次 7 → set size=1；multiset size=5，count(7)=5（预期：分清两个容器）。
> 4. 严格递增：插 1..5 → 树右斜，自平衡后查找仍 O(log n)（预期：输出 1 2 3 4 5）。
> 5. 严格递减：插 5..1 → 同上反转（预期：输出 1 2 3 4 5，体会"与插入序无关"）。
> 6. 极值：n=1e6 次 find → 约 10^6 乘 20 次比较瞬间完成；换数组线性扫描是 10^12 次，必超时（预期：复杂度差距落到具体数字）。

### 【P0】4. 迭代器与竞赛 STL 速查：统一的访问与算法界面

前置依赖：[[STL]]、[[排序]]、[[二分]]｜后续衔接：[[排序]]（sort 的内部思想与手写版）、[[二分]]（lower_bound 的手写版与题面应用）
关联错题：暂无

**① 结论与识别信号**：迭代器提供访问容器中对象的方法，如同一个指针——begin() 指向第一个元素，end() 指向最后一个元素的下一个位置，区间 [begin, end) 前闭后开；sort/lower_bound/binary_search/accumulate 等算法只认迭代器，同一套函数排遍一切容器与数组（算法集中在 \<algorithm\> 与 \<numeric\>）。识别信号：看到"有序数组里找第一个不小于 x 的数"就想到 lower_bound，"统计差为定值的数对"就想到排序加两边界相减，"一大堆数求和"就想到 accumulate 且初值写 0LL。

**② 数据推演结果**：v = {1,3,5,7,9} 已排序，lower_bound 找 6 → 返回下标 3（值 7）；{2,2,2} 中 upper_bound(2) - lower_bound(2) = 3 = 值为 2 的元素个数。

**③ 核心结论与推导链**：推导链——区间设计成前闭后开 [begin, end) → 空区间统一表示为 begin == end（无需"end 是否合法"的特判）、循环条件 `it != end` 对所有容器成立（list 做不了 end-1 也无妨）→ 算法收迭代器不收容器 → `sort(a, a+n)`（C 数组）与 `sort(v.begin(), v.end())`（vector）通用，这正是知识点 1"数据结构和算法的分离"落到接口上的样子。

**④ 代码与追踪**：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>   // sort / lower_bound / binary_search
#include <numeric>     // accumulate
using namespace std;
int main() {
    vector<int> v = {9, 1, 7, 3, 5};                  // 等价 C：int v[5]={...};
    sort(v.begin(), v.end());                         // 升序 O(n log n)；降序加 greater<int>()
    bool has = binary_search(v.begin(), v.end(), 7);  // 前提：区间已排序，返回 bool
    auto it = lower_bound(v.begin(), v.end(), 6);     // 第一个 >= 6 的迭代器
    int pos = it - v.begin();                         // 迭代器相减 = 下标，等价 C：指针相减
    long long sum = accumulate(v.begin(), v.end(), 0LL);  // 初值 0LL：决定按 long long 累加
    cout << pos << " " << has << " " << sum << "\n";  // 3 1 25
    return 0;                                         // reverse/count 见学习版素材 mycode.cpp
}
```

执行追踪表（lower_bound 找 6，v 已排序为 {1,3,5,7,9}，二分区间 [lo, hi)）：

| 步骤 | 当前元素 | 结构状态 | 动作 | 结果 |
|:---:|:---:|:---|:---|:---|
| 1 | 区间 [0,5) | {1,3,5,7,9} | mid=2，值 5 < 6，答案在右半 | lo=3 |
| 2 | 区间 [3,5) | {7,9} | mid=4，值 9 >= 6，答案在左半含自身 | hi=4 |
| 3 | 区间 [3,4) | {7} | mid=3，值 7 >= 6 | hi=3 |
| 4 | 区间 [3,3) | 空 | lo==hi，停止 | 返回下标 3，值 7 |

**⑤ 真题索引**：

- 洛谷 P1102 A-B 数对：统计数对 A-B=C——排序后对每个 a 查 a-C 的个数，`upper_bound - lower_bound` 一次得出，总复杂度 O(n log n)；暴力二重循环 O(n^2) 在 n=2e5 时超时。
- 洛谷 P1177【模板】快速排序：本节 sort 是它的最后一块拼图（知识点 2 已引用）。
- 迁移题（自编）：有序数组求大于等于 x 的最小值，不存在输出 -1——lower_bound 得 it，`it == v.end()` 时输出 -1，否则输出 `*it`，正是 [[二分]] 手写模板的库函数版。

**⑥ 坑点与边界数据集**：

> [!caution]
> **【易错】** 对未排序区间调 lower_bound 或 binary_search——前提崩塌，返回值无意义（答案错）。
> 错误写法：`auto it = lower_bound(v.begin(), v.end(), 6);`（v = {9,1,7,3,5} 未排序）；正确写法：`sort(v.begin(), v.end());` 之后再二分。

> [!caution]
> **【易错】** accumulate 初值写 0——初值类型决定累加类型，按 int 累加时 1e5 个 1e9 相加溢出为负数。
> 错误写法：`int s = accumulate(v.begin(), v.end(), 0);`；正确写法：`long long s = accumulate(v.begin(), v.end(), 0LL);`（实测：1e5 个 1e9，int 版溢出，0LL 版得 1e14）。另注意 end 不指向有效元素——`*v.end()` 是越界，"最后一个元素"用 v.back()。

> [!caution]
> **【易错】** 比较器写 <=——相等元素"互为更小"，违反严格弱序，sort 内部越界（RE）。
> 错误写法：`bool cmp(int a, int b) { return a <= b; }`；正确写法：`bool cmp(int a, int b) { return a > b; }`——严格弱序要求相等时必须返回 false。

> [!example]-
> **边界数据集（先自己跑一遍，再展开对照）**
> 1. 空输入：sort/lower_bound 作用于空 vector → begin==end，零次比较（预期：无输出不崩）。
> 2. 单元素：{5} 中 lower_bound(5) → 下标 0；lower_bound(6) → end()（预期：判 end 再解引用）。
> 3. 全相同：{2,2,2} 中 lower_bound(2) → 下标 0，upper_bound(2) → end()，两者相减 = 3 = 个数（预期：掌握"个数 = 两边界之差"）。
> 4. 严格递增：{1,3,5,7,9} 查 6 → 下标 3（预期：与追踪表一致）。
> 5. 严格递减：不适用：lower_bound 要求升序区间；递减区间需先 reverse 或传比较器（预期：理解前提）。
> 6. 极值：1e5 个 1e9 求和 → 初值 0 的 int 版溢出为负数，0LL 版得 1e14（预期：溢出可测，学习版附录 B-5 已验证）。

## 二、易错总表

| # | 坑 | 正解 |
|---|-----|------|
| 1 | 空容器上 top()/front()/pop() | 先判 empty 再操作（知识点 1） |
| 2 | 遍历中 push_back/insert；resize 与 reserve 混用 | 先记规模再插入；resize 造元素、reserve 只留槽位（知识点 2） |
| 3 | map 用 [] 判存在 | find/count；[] 会插入默认值（知识点 3） |
| 4 | set.count 当计数用 | set 恒不超过 1；计数用 multiset 或 map（知识点 3） |
| 5 | 遍历中 erase 后继续 ++ | 用 erase 返回值接续（知识点 3） |
| 6 | lower_bound 前忘排序 | 先 sort，前提是升序区间（知识点 4） |
| 7 | accumulate 初值写 0 | 写 0LL，初值类型决定累加类型（知识点 4） |
| 8 | 比较器写 <= | 严格弱序：相等返回 false（知识点 4） |

## 三、待补知识点清单

| 知识点 | 一句话补全 | 优先级 |
|--------|-----------|--------|
| 红黑树平衡细节（旋转与染色） | set/map 只用到"自平衡二叉搜索树"这层结论，旋转细节待 [[红黑树]] 补 | P2 |
| string/deque/list 完整 API | 学习版并入知识点 1 的选型叙述，未单独成卡，用到时回 [[STL]] 查素材代码组 | P2 |
| 严格弱序比较器的正式定义 | 竞赛层面记住"相等时必须返回 false"即可，正式定义待补 | P1 |

## 四、口诀集

1. 选型口诀：随机访问 vector，两端进出 deque，自动排序去重 set，键值映射 map，先进后出/先出 stack/queue（适配器，不可遍历）。
2. 扩容口诀：满了翻倍搬一次，均摊尾插常数级；已知规模先 reserve，中间扩容全省去。
3. set/map 口诀：查存在用 find，中括号会插赃；计数找 multiset，set 的 count 只是一。
4. 算法口诀：先排再二分，个数两边界差，求和初值 0LL，比较器相等返 false。

## 五、自测清单

- [ ] 能说出同一批数据在 vector/set/map 中的三种结果并解释原因
- [ ] 能手推连插 1..8 的 size/capacity 序列并说出均摊 O(1) 的求和依据
- [ ] 能说清 map 的 [] 与 find 的差异及各自后果
- [ ] 能默写 sort + lower_bound + accumulate 速查并解释 0LL 的作用
- [ ] 能手推 lower_bound 找 6 的四步追踪表，并说出"个数 = upper_bound − lower_bound"

## 六、问题日志

> 每条错题按以下七字段登记（替代旧错题登记表；与 P0 卡「关联错题」行双向可达）：

```text
### [题目编号与名称] - [日期]
- 做题模式：[独立通过 / 提示后通过 / 看题解]
- 最初的错误假说：我一开始以为____，理由是____
- 卡点根因分类（勾选）：[ ] 概念知识盲区　[ ] 建模抽象失败　[ ] 边界/溢出细节崩溃　[ ] 审题失败
- 关键破局思维：原来「____」能把问题化为____
- 题目信号锚点：题面出现「____」时该想到____
- 对应卡片：[[STL复习回顾#【P0】知识点名]]
- 同类关联题号：____
- 复盘追问：7 天后这题我还能独立通过吗？（到期自测）
```

### 错题登记（学完后追加，同步回填对应 P0 卡的「关联错题」行）

| 题号 | 错因 | 对应卡片 |
|------|------|---------|
| （学完后填写） | | |

## 交付前自检清单

- [x] 知识地图与学习版对账，无遗漏；知识点清单 4 对 4（编号/顺序/名称/优先级一致）
- [x] 六步详略对照执行：①②③留结论、④代码与追踪表完整、⑤题号思路片段、⑥坑点与数据集全保留
- [x] 每张卡①节识别信号为题型语/输入特征，非名称换词；四张卡均含「关联错题」行
- [x] 文本树为主，mermaid 0 个；⑥节边界数据集为折叠 callout（`> [!example]-`，声明行独占一行）
- [x] 知识连接（前置/后续、关联错题、对应卡片）均用 `[[]]` 双链，含节锚点
- [x] 全文无 emoji；无「显然 / 易得 / 略」类措辞；表格不超过 6 列
- [x] 易错总表编号可回查；口诀集每主题至少一条；问题日志为七字段模板
- [x] frontmatter 含「最后复习日期」；不确定处显式标注；待补清单已列出
- [x] 篇幅为学习版（约 480 行）的 1/2~2/3 区间，六步完整性与坑点完整性优先于行数
