/*树状数组
区间修改单点查询模板
写法2,利用差分和前缀和
*/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;

const int MAXN = 500010;

int n, m, t, x, y, k;
struct BIT {
    /*差分+前缀和写法*/
    int a[MAXN];
    void add(int x, int v) {
        for (; x <= n; x += x & (-x)) {
            a[x] += v;
        }
    }
    int Qsum(int x) {
        int ans = 0;
        for (; x; x -= x & (-x)) {
            ans += a[x];
        }
        return ans;
    }
} bit;

int main() {
    scanf("%d%d", &n, &m);
    int t1 = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &t);
        bit.add(i, t - t1);
        t1 = t;
    }
    while (m--) {
        scanf("%d%d", &t, &x);
        if (t == 1) {
            scanf("%d%d", &y, &k);
            bit.add(x, k);
            bit.add(y + 1, -k);
        } else if (t == 2) {
            printf("%d\n", bit.Qsum(x));
        }
    }
    return 0;
}