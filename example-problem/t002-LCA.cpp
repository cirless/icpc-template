/* source: https://codeforces.com/problemset/problem/519/E
一个图论中树问题的母题，LCA最近公共祖先+树形dp
*/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
typedef long long LL;
const int MAXN = 200110;

/*io优化 */
inline int readint() {
    int ans = 0, flag = 0;
    char ch;
    while (~(ch = getchar()) && (ch < '0' || ch > '9') && ch != '-')
        ;
    ch == '-' ? flag = 1 : ans = ch - '0';
    while (~(ch = getchar()) && (ch >= '0' && ch <= '9'))
        ans = (ans << 1) + (ans << 3) + ch - '0';
    (flag) && (ans = -ans);
    return ans;
}

inline void print(int x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
    /* printf("%d",x);*/
}

/*建无向图*/
int n, m;
int g[MAXN], to[MAXN], v[MAXN], nextn[MAXN], eid = 0;
void addedge(int x, int y) {
    to[++eid] = y, nextn[eid] = g[x], g[x] = eid;
    to[++eid] = x, nextn[eid] = g[y], g[y] = eid;
}

/*建树*/
int depth[MAXN],
    fa[MAXN][33];  // fa[x][i]表示第x个节点的2^i层祖先，不存在用-1表示
int sonsum[MAXN];  // sonsum[x]表示x结点的包括x自己的子孙数量

void dfs(int nfa, int nu)  //以nu为根的子树，其父节点为nfa
{
    // printf("nfa=%d nu=%d\n",nfa,nu);
    if (nfa != 0)
        depth[nu] = depth[nfa] + 1;  //树的逻辑深度
    else
        depth[nu] = 1;
    fa[nu][0] = nfa;
    for (int i = 1; i < 20; i++)
        if (fa[nu][i - 1] != 0)
            fa[nu][i] = fa[fa[nu][i - 1]][i - 1];
    sonsum[nu] = 1;  //子孙数量先包含自己

    for (int i = g[nu]; i != -1; i = nextn[i]) {
        if (to[i] != nfa) {
            // printf("i=%d nfa=%d nu=%d to=%d \n",i,nfa,nu,to[i]);
            dfs(nu, to[i]);
            sonsum[nu] += sonsum[to[i]];
        }
    }
}
void buildtree(int root) {
    memset(fa, 0, sizeof(fa));
    memset(depth, 0, sizeof(depth));
    memset(sonsum, 0, sizeof(sonsum));
    dfs(0, root);
}
int LCA(int a, int b)  //用倍增法找a和b的最近公共祖先（包括他们自己）
{
    if (a == b)
        return a;
    int t;
    (depth[a] < depth[b]) && (t = a, a = b, b = t);
    //先将a提升到和b同样的深度
    for (int i = 19; i >= 0; i--) {
        if (depth[a] - (1 << i) >= depth[b])
            a = fa[a][i];
    }
    if (a == b)
        return a;
    // a和b同步倍增上升
    for (int i = 19; i >= 0; i--) {
        if (fa[a][i] != fa[b][i])
            a = fa[a][i], b = fa[b][i];
    }
    return fa[a][0];
}
int findson(int u, int sun)  //找u结点的一个儿子结点，使得sun结点是其子孙节点
{
    int a = sun;
    /*TLE暴力解法
    int i, ufa = fa[u][0];
    for (i = g[u]; i != -1; i = nextn[i])
    {
        if (to[i] != ufa)
        {
            if (LCA(sun, to[i]) == to[i])
                return to[i];
        }
    }
    return -1; //没找到*/
    for (int i = 19; i >= 0; i--) {
        if (depth[a] - (1 << i) > depth[u])
            a = fa[a][i];
    }
    // printf("findson(%d,%d)=%d\n",u,sun,a);
    return a;
}
int degree[MAXN];

int main() {
    n = readint();
    int u, v, c;
    memset(nextn, -1, sizeof(nextn));
    memset(g, -1, sizeof(g));

    for (int i = 1; i < n; i++) {
        u = readint();
        v = readint();
        degree[u]++, degree[v]++;
        addedge(u, v);
    }
    int root = 1;
    for (int i = 2; i <= n; i++)
        if (degree[i] > degree[root])
            root = i;
    buildtree(root);
    m = readint();
    // for (int i = 1; i <= n; i++) printf("sonsum[%d]=%d depth[%d]=%d\n", i,
    // sonsum[i], i, depth[i]);
    for (int i = 1; i <= m; i++) {
        u = readint();
        v = readint();
        if (depth[u] < depth[v])
            swap(u, v);
        int lca = LCA(u, v), lcalen, middep, ans, a = u;
        lcalen = depth[u] + depth[v] - 2 * depth[lca];
        if (u == v)
            ans = n;
        else if ((lcalen & 1) == 1) {
            ans = 0;
        } else {
            middep = depth[u] - lcalen / 2;
            if (depth[u] == depth[v]) {
                ans = n - sonsum[findson(lca, u)] - sonsum[findson(lca, v)];
            } else {
                for (int i = 19; i >= 0; i--) {
                    if (depth[a] - (1 << i) >= middep)
                        a = fa[a][i];
                }
                ans = sonsum[a] - sonsum[findson(a, u)];
            }
        }
        print(ans);
        putchar('\n');
    }
    return 0;
}