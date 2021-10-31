#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;

// 朴素的快速幂，在MOD>INT_MAX时可能乘法溢出
ll __qpow(ll a, ll n, ll MOD) {
    ll ans = 1ll;
    while (n > 0) {
        if (n & 1ll) {
            ans *= a;
            ans %= MOD;
        }
        n >>= 1;
        a = (a * a) % MOD;
    }
    return ans;
}

// 快速乘
ll qmul(ll a, ll b, ll MOD) {
    ll ans = 0, res = a;
    while (b > 0) {
        if (b & 1)
            ans = (ans + res) % MOD;
        res = (res + res) % MOD;
        b >>= 1;
    }
    return ans;
}
/* 快速幂 */
ll qpow(ll a, ll n, ll MOD) {
    ll ans = 1ll, res = a;
    while (n > 0) {
        if (n & 1)
            ans = qmul(ans, res, MOD);
        res = qmul(res, res, MOD);
        n >>= 1;
    }
    return ans;
}