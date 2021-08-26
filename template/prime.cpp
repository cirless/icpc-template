/*
质数筛模板，主要对例题t007进行了封装
使用线性复杂度的筛法求出质数表
*/
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

struct PrimeShaker {
    vector<bool> iscom;
    int n;
    vector<int> prime;
    // 参数n为筛的大小，筛会在1~n之间生成质数表
    PrimeShaker(int n) : n(n), iscom(n + 10,0) {
        for (int i = 2; i <= n; i++) {
            if (!iscom[i])
                prime.push_back(i);
            for (int j = 0; j < prime.size() && i * prime[j] <= n; j++) {
                iscom[i * prime[j]] = 1;
                if (i % prime[j] == 0)
                    break;
            }
        }
    };
    int primenum(){return prime.size();}
};
int main() {
    freopen("prime.out", "w", stdout);
    PrimeShaker shaker(1000000);
    for (int i = 0; i < shaker.primenum(); i++)
        printf("%d:%d ", i, shaker.prime[i]);
    return 0;
}
