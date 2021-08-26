/* 
欧拉筛模板，使用线性复杂度的筛法求出质数表，并基于此求出欧拉函数
*/
#include <cstdio>
#include <cstring>
#define MAXN 100010
bool iscom[MAXN];
int prime[MAXN], cnt = 0, phi[MAXN], n;
void shaker() {
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (iscom[i] == 0)
            prime[++cnt] = i, phi[i] = i - 1;
        for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
            iscom[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            //特判，当i为prime[j]倍数时，只需乘prime[j]即可
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            //一般情况，互质时函数有积性
        }
    }
}
int main() {
    freopen("欧拉筛输出样例.out", "w", stdout);
    n = MAXN;
    shaker();
    for (int i = 1; i <= n; i++)
        printf("phi[%d]=%d ", i, phi[i]);
    return 0;
}
