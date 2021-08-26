/* source: https://www.luogu.com.cn/problem/P3367
并查集模板
*/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
typedef long long LL;
using namespace std;
const int MAXN = 10010, MAXM = 200010;
int n, m, fa[MAXN];

/*递归找祖先结点*/
int find(int x) {
    if (fa[x] == x)
        return x;
    return fa[x] = find(fa[x]);
}
/*循环找祖先结点*/
int find2(int x) {
    if (fa[x] == x)
        return x;
    while (fa[x] != x)
        x = fa[x] = fa[fa[x]];
    return x;
}
int main() {
    scanf("%d%d", &n, &m);
    int x, y, z;
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &z, &x, &y);
        if (z == 1) {
            fa[find2(x)] = find2(y);
        } else {
            if (find2(x) == find2(y))
                printf("Y\n");
            else
                printf("N\n");
        }
    }
    return 0;
}