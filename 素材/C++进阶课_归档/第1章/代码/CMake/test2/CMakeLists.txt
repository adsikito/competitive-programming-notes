// 递归与分治篇断言验证：官方样例 + 暴力对拍 + 汉诺塔移动序列逐字符对拍
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cassert>
#include <string>
using namespace std;

// ---- LC53 最大子数组：分治（与素材源码同逻辑） ----
int maxxmid(vector<int>& nums, int l, int mid, int r) {
    int lmax = INT_MIN, sum = 0;
    for (int i = mid; i >= l; i--) { sum += nums[i]; lmax = max(lmax, sum); }
    int rmax = INT_MIN; sum = 0;
    for (int i = mid + 1; i <= r; i++) { sum += nums[i]; rmax = max(rmax, sum); }
    return lmax + rmax;
}
int maxxans(vector<int>& nums, int l, int r) {
    if (l == r) return nums[l];
    int mid = (l + r) / 2;
    int a1 = maxxans(nums, l, mid);
    int a2 = maxxans(nums, mid + 1, r);
    int a3 = maxxmid(nums, l, mid, r);
    return max(max(a1, a2), a3);
}
// 暴力：枚举所有区间 O(n^2)
int bruteMax(vector<int>& a) {
    int best = INT_MIN;
    for (int i = 0; i < (int)a.size(); i++) {
        int s = 0;
        for (int j = i; j < (int)a.size(); j++) { s += a[j]; best = max(best, s); }
    }
    return best;
}

// ---- 汉诺塔：展示版（移动序列）与计数版 ----
string moves;
void moveShow(int x, char s, char e, char h) {   // 展示版：x 个盘子 s 借 h 到 e
    if (x == 1) { moves += string(1, '0' + x); moves += " "; moves += s; moves += "--->"; moves += e; moves += "\n"; return; }
    moveShow(x - 1, s, h, e);
    moves += string(1, '0' + x); moves += " "; moves += s; moves += "--->"; moves += e; moves += "\n";
    moveShow(x - 1, h, e, s);
}
long long moveCount(int n) {                     // 计数版：T(n)=2T(n-1)+1
    if (n == 1) return 1;
    return 2 * moveCount(n - 1) + 1;
}

int main() {
    // 1. LC53 官方样例：[-2,1,-3,4,-1,2,1,-5,4] -> 6
    vector<int> s1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    assert(maxxans(s1, 0, 8) == 6);
    // 2. LC53 分治 vs 暴力对拍（n=1..8，300 组随机）
    srand(20260926);
    for (int t = 0; t < 300; t++) {
        int n = 1 + rand() % 8;
        vector<int> a(n);
        for (auto &x : a) x = rand() % 41 - 20;
        assert(maxxans(a, 0, n - 1) == bruteMax(a));
    }
    // 3. 汉诺塔 n=3 移动序列逐字符对拍（经典 7 步）
    moves.clear();
    moveShow(3, 'a', 'c', 'b');
    string expect = "1 a--->c\n2 a--->b\n1 c--->b\n3 a--->c\n1 b--->a\n2 b--->c\n1 a--->c\n";
    assert(moves == expect);
    // 4. 汉诺塔移动计数 T(n)=2^n-1（n=1..20）
    for (int n = 1; n <= 20; n++) assert(moveCount(n) == ((1LL << n) - 1));
    // 5. 自编小样例：分治在 [4,-1,2] 上返回 5（正文追踪表同源）
    vector<int> s2 = {4, -1, 2};
    assert(maxxans(s2, 0, 2) == 5);
    cout << "ALL PASS: 5 groups (sample + brute + hanoi-sequence + count + trace case)" << endl;
    return 0;
}
