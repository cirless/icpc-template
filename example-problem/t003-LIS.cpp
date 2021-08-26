/* source: https://acm.hdu.edu.cn/showproblem.php?pid=1950
O(nlogn)时间内解出LIS（最长递增子序列）的长度，不要求输出结果序列
*/
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>
using namespace std;
typedef long long LL;
int n, p, a[40010];
int b[40010], blen;
int main() {
    scanf("%d", &n);
    while (n--) {
        memset(b, 0, sizeof(b));
        scanf("%d", &p);
        for (int i = 1; i <= p; i++)
            scanf("%d", &a[i]);
        b[1] = a[1];
        blen = 1;
        for (int i = 2; i <= p; i++) {
            int* p = upper_bound(b + 1, b + blen + 1, a[i]);
            if (p == (b + blen + 1))
                b[++blen] = a[i];
            else {
                *p = a[i];
            }
        }
        printf("%d\n", blen);
    }
    return 0;
}
