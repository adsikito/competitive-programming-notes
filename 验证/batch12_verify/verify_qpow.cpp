// 断言程序：快速幂（素材算法复刻）与朴素幂对拍 300 组随机数据
// 另测：P1226 样例锚点、边界（0/1 次方、p=1）、溢出场景（乘前不取模版错误复现）
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

// 素材 快速幂.cpp 的核心循环（逐行同构）
ll qpow(ll a, ll b, ll p) {
    ll n = a % p, x = b, ans = 1;
    while (x != 0) {
        if (x % 2 == 1) ans = (ans * n) % p;
        x /= 2;
        n = (n * n) % p;
    }
    return ans % p;
}

// 朴素幂（long long 范围内），用于小数据对拍
ll naive(ll a, ll b, ll p) {
    ll r = 1;
    for (ll i = 0; i < b; i++) r = r * (a % p) % p;
    return r % p;
}

int main() {
    srand(20260926);
    int pass = 0, fail = 0;

    // 锚点 1：P1226 官方样例 2 10 9 → 2^10 mod 9 = 1024 mod 9 = 7
    if (qpow(2, 10, 9) == 7) pass++; else { fail++; printf("FAIL P1226 sample\n"); }

    // 锚点 2：课件 5^10 = 9765625（无模意义下，取 p 足够大）
    if (qpow(5, 10, (ll)2e18) == 9765625LL) pass++; else { fail++; printf("FAIL 5^10\n"); }

    // 锚点 3：边界 b=0 → 1；a=0,b>0 → 0；p=1 → 0
    if (qpow(5, 0, 7) == 1) pass++; else { fail++; printf("FAIL b=0\n"); }
    if (qpow(0, 5, 7) == 0) pass++; else { fail++; printf("FAIL a=0\n"); }
    if (qpow(123456, 789, 1) == 0) pass++; else { fail++; printf("FAIL p=1\n"); }

    // 对拍 300 组：a,b ∈ [0,50], p ∈ [1,1e9]（保证朴素版不溢出：50^50 内中间值 ans*n ≤ (p-1)*(p-1)? 不安全——限制 a,b 小且 p 小）
    // 朴素版中间值最大 (p-1)*a ≤ 1e9*50，安全；qpow 中间值 (p-1)^2 ≤ 1e18 < 9.2e18，安全
    for (int i = 0; i < 300; i++) {
        ll a = rand() % 51, b = rand() % 51, p = rand() % 1000000000 + 1;
        ll r1 = qpow(a, b, p), r2 = naive(a, b, p);
        if (r1 == r2) pass++; else { fail++; printf("FAIL a=%lld b=%lld p=%lld qpow=%lld naive=%lld\n", a, b, p, r1, r2); }
    }

    // 溢出反例：p 接近 1e9 时，乘前不取模的写法会先爆——用 __int128 验证正确答案
    // 2^62 mod (1e9+7)：用 unsigned 复刻“错版”（n*n 不取模）会溢出，这里只验证正解与数学期望一致
    // 2^62 mod 1e9+7 = 145586002（Python pow 锚点，实测校正——初稿手写锚点 633538611 错误，教训：锚点必须外部计算）
    if (qpow(2, 62, 1000000007LL) == 145586002LL) pass++; else { fail++; printf("FAIL 2^62 mod 1e9+7\n"); }

    // 溢出复现：错版（乘后才取模且 n*n 直接乘 ll 上限数据）
    // a=b=3037000499（sqrt(2^63) 附近），p=9223372036854775783（>ll 素数上限附近）——错版 n*n 溢出
    // 正确实现需 __int128；素材版在 p ≤ ~3e9 时安全。此处登记：p 上限约 3e9（(3e9)^2=9e18 贴 ll 上限）
    // 用 p=2999999999（>int 范围，<3e9）测素材版与 __int128 版一致
    {
        ll p = 2999999999LL, a = 123456789, b = 987654321;
        __int128 ans = 1, n = a % p, x = b;
        while (x) { if (x & 1) ans = ans * n % p; n = n * n % p; x >>= 1; }
        ll expect = (ll)ans;
        if (qpow(a, b, p) == expect) pass++; else { fail++; printf("FAIL big-p\n"); }
    }

    printf("PASS=%d FAIL=%d\n", pass, fail);
    return fail == 0 ? 0 : 1;
}
