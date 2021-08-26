/* source: https://acm.hdu.edu.cn/showproblem.php?pid=6608
数论中Wilson定理和Fermat小定理的一个应用
使用Rabin-Miller测试，在一定范围内(0~2^64-1或int128的范围)能准确地以常数时间判断一个数是否为质数
*/
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long ll;

ll MOD;

ll power(ll x, unsigned long long y, ll p) {
    ll res = 1LL;
    x = x % p;
    while (y > 0) {
        if (y & 1LL)
            res = (res * x) % p;
        y = y >> 1LL;
        x = (x * x) % p;
    }
    return res;
}

ll prime[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

ll qm(ll a, ll b, ll c) {
    long long ans = 0, res = a;
    while (b) {
        if (b & 1)
            ans = (ans + res) % c;
        res = (res + res) % c;
        b >>= 1;
    }
    return (ll)ans;
}
ll mul(ll a, ll b) {
    return (ll)(__int128(a) * b % MOD);
}
ll qp(ll a, ll b, ll c) {
    ll ans = 1, res = a;
    while (b) {
        if (b & 1)
            ans = qm(ans, res, c);
        res = qm(res, res, c);
        b >>= 1;
    }
    return ans;
}
__int128 qp2(__int128 a, __int128 b, __int128 c) {
    __int128 ans = 1, res = a;
    while (b) {
        if (b & 1)
            ans = qm(ans, res, c);
        res = qm(res, res, c);
        b >>= 1;
    }
    return ans;
}
bool Miller_Rabin(ll x) {
    ll i, j, k;
    ll s = 0, t = x - 1;
    if (x == 2)
        return true;
    if (x < 2 || !(x & 1))
        return false;
    while (!(t & 1)) {
        s++;
        t >>= 1;
    }
    for (i = 0; i < 6 && prime[i] < x; ++i) {
        ll a = prime[i];
        ll b = qp(a, t, x);
        for (j = 1; j <= s; ++j) {
            k = qm(b, b, x);
            if (k == 1 && b != 1 && b != x - 1)
                return false;
            b = k;
        }
        if (b != 1)
            return false;
    }
    return true;
}

__int128 modInverse(__int128 a, __int128 p) {
    return qp(a, p - 2ll, p);
}

ll modFact(ll n, ll p) {
    if (p <= n)
        return 0;
    __int128 res = (p - 1ll);
    for (__int128 i = n + 1ll; i < p; i++) {
        res = ((res % p) * (modInverse(i, p) % p)) % p;
    }
    return (ll)res;
}

int main() {
    ll t;
    scanf("%lld", &t);
    while (t-- > 0) {
        scanf("%lld", &MOD);
        ll i;
        for (i = MOD - 1; i > MOD - 2001; i--) {
            if (Miller_Rabin(i))
                break;
        }
        printf("%lld\n", modFact(i, MOD));
    }
    return 0;
}