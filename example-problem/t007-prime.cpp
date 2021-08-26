/* 
质数筛模板，使用线性复杂度的筛法求出质数表
*/
#include <cstdio>
#include <cstring>
#define MAXN 1000000
bool iscom[MAXN];
int prime[MAXN], cnt = 0, n;
void shaker() {
    for (int i = 2; i <= n; i++) {
        if (!iscom[i])
            prime[++cnt] = i;
        for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
            iscom[i * prime[j]] = 1;
            //			printf("%d*%d=%d ",i,prime[j],i*prime[j]);
            if (i % prime[j] == 0)
                break;
        }
        //		printf("\n");
    }
}

int main() {
    freopen("质数筛输出样例.out", "w", stdout);
    n = MAXN;
    shaker();
    for (int i = 1; i <= cnt; i++)
        printf("%d:%d ", i, prime[i]);
    return 0;
}
