/*
数论中Wilson定理和Fermat小定理的一个应用
使用Rabin-Miller测试，在一定范围内(0~2^64-1或int128的范围)能准确地以常数时间判断一个数是否为质数
*/

#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

// Rabin-Miller测试的整个算法为一个静态类，只有静态成员，没有需要外部输入的预处理参数
struct Miller_Rabin {
    static const ll prime[7];
    // 快速乘法
    static ll qm(ll a, ll b, ll c) {
        long long ans = 0, res = a;
        while (b) {
            if (b & 1)
                ans = (ans + res) % c;
            res = (res + res) % c;
            b >>= 1;
        }
        return (ll)ans;
    }
    // 快速幂
    static ll qp(ll a, ll b, ll c) {
        ll ans = 1, res = a;
        while (b) {
            if (b & 1)
                ans = qm(ans, res, c);
            res = qm(res, res, c);
            b >>= 1;
        }
        return ans;
    }
    // 检验x是否为质数
    static bool check(ll x) {
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
};
const ll Miller_Rabin::prime[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

int main() {
    // check检验函数的使用样例
    cout << Miller_Rabin::check(998244353);
}