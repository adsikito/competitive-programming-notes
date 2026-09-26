// 贪心篇断言验证：官方样例 + 小数据暴力对拍
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>
#include <cassert>
using namespace std;

// ---- P1090 合并果子：优先队列贪心（与素材源码同逻辑） ----
long long mergeGreedy(vector<long long> a) {
    priority_queue<long long, vector<long long>, greater<long long>> q(a.begin(), a.end());
    long long ans = 0;
    while ((int)q.size() > 1) {
        long long x = q.top(); q.pop();
        long long y = q.top(); q.pop();
        ans += x + y;
        q.push(x + y);
    }
    return ans;
}
// 暴力：枚举每次任选两堆合并的全部顺序，取总代价最小（n<=5 规模可枚举）
void dfsMerge(vector<long long> v, long long cost, long long &best) {
    if ((int)v.size() == 1) { best = min(best, cost); return; }
    for (int i = 0; i < (int)v.size(); i++)
        for (int j = i + 1; j < (int)v.size(); j++) {
            vector<long long> nv;
            for (int k = 0; k < (int)v.size(); k++)
                if (k != i && k != j) nv.push_back(v[k]);
            nv.push_back(v[i] + v[j]);
            dfsMerge(nv, cost + v[i] + v[j], best);
        }
}

// ---- P4995 跳跳！：排序 + 高低交替贪心（与素材源码同逻辑） ----
long long jumpGreedy(vector<long long> h) {
    h.insert(h.begin(), 0);          // 地面高度 0
    sort(h.begin(), h.end());
    int l = 0, r = (int)h.size() - 1;
    long long ans = 0;
    while (l < r) {
        ans += (h[r] - h[l]) * (h[r] - h[l]); l++;
        ans += (h[r] - h[l]) * (h[r] - h[l]); r--;
    }
    return ans;
}
// 暴力：全排列跳序，取体力最大（n<=6）
long long jumpBrute(vector<long long> h) {
    long long best = 0;
    sort(h.begin(), h.end());
    do {
        long long cur = 0, prev = 0;
        for (long long x : h) { cur += (x - prev) * (x - prev); prev = x; }
        best = max(best, cur);
    } while (next_permutation(h.begin(), h.end()));
    return best;
}

// ---- LC2611 小老鼠吃奶酪：差值排序贪心（与素材源码同逻辑） ----
long long miceGreedy(vector<long long> r1, vector<long long> r2, int k) {
    int n = r1.size();
    vector<long long> d(n);
    long long ans = 0;
    for (int i = 0; i < n; i++) { d[i] = r1[i] - r2[i]; ans += r2[i]; }
    sort(d.begin(), d.end());
    for (int i = n - 1; i >= n - k; i--) ans += d[i];
    return ans;
}
// 暴力：枚举给 1 号鼠的 k 块奶酪组合（n<=8）
long long miceBrute(vector<long long> r1, vector<long long> r2, int k) {
    int n = r1.size();
    vector<int> sel(n, 0);
    for (int i = n - k; i < n; i++) sel[i] = 1;
    long long best = LLONG_MIN;
    do {
        long long cur = 0;
        for (int i = 0; i < n; i++) cur += (sel[i] ? r1[i] : r2[i]);
        best = max(best, cur);
    } while (next_permutation(sel.begin(), sel.end()));
    return best;
}

int main() {
    // 1. P1090 官方样例：n=3, 1 2 9 -> 15
    assert(mergeGreedy({1, 2, 9}) == 15);
    // 2. P1090 小数据暴力对拍（n=1..5，200 组随机）
    srand(20260926);
    for (int t = 0; t < 200; t++) {
        int n = 1 + rand() % 5;
        vector<long long> a(n);
        for (auto &x : a) x = 1 + rand() % 20;
        long long best = LLONG_MAX;
        dfsMerge(a, 0, best);
        assert(mergeGreedy(a) == best);
    }
    // 3. P4995 官方样例 1：{2,1} -> 5；样例 2：{6,3,5} -> 49
    assert(jumpGreedy({2, 1}) == 5);
    assert(jumpGreedy({6, 3, 5}) == 49);
    // 4. P4995 小数据暴力对拍（n=1..6，200 组随机）
    for (int t = 0; t < 200; t++) {
        int n = 1 + rand() % 6;
        vector<long long> h(n);
        for (auto &x : h) x = 1 + rand() % 30;
        assert(jumpGreedy(h) == jumpBrute(h));
    }
    // 5. LC2611 官方示例 1：reward1=[1,1,3,4] reward2=[4,4,1,1] k=2 -> 15
    assert(miceGreedy({1, 1, 3, 4}, {4, 4, 1, 1}, 2) == 15);
    // 6. LC2611 小数据暴力对拍（n=1..8，200 组随机）
    for (int t = 0; t < 200; t++) {
        int n = 1 + rand() % 8;
        int k = rand() % (n + 1);
        vector<long long> r1(n), r2(n);
        for (auto &x : r1) x = rand() % 20;
        for (auto &x : r2) x = rand() % 20;
        assert(miceGreedy(r1, r2, k) == miceBrute(r1, r2, k));
    }
    cout << "ALL PASS: 6 groups (samples + brute-force cross-checks)" << endl;
    return 0;
}
