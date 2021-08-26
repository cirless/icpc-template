/*树状数组
单点修改区间查询模板
*/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;

const int MAXN = 500010;

int n, m, t, x, y;
struct BIT {
    int a[MAXN];
    void add(int x, int v) {
        for (; x <= n; x += x & (-x)) {
            a[x] += v;
        }
    }
    int Qsum(int x) {
        int ans = 0;
        for (; x > 0; x -= x & (-x)) {
            ans += a[x];
        }
        return ans;
    }
} bit;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &t);
        bit.add(i, t);
    }
    while (m--) {
        scanf("%d%d%d", &t, &x, &y);
        if (t == 1) {
            bit.add(x, y);
        } else if (t == 2) {
            printf("%d\n", bit.Qsum(y) - bit.Qsum(x - 1));
        }
    }
    return 0;
}