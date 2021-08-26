/*CF500D New Year Santa Network
树形dp
先将三元组转化为二元组
三元组(a,b,c)中有C(n,3)*3条最短路,转化为二元组(a,b)即两两结点之间最短路C(n,2)*(n-2)条
累计每两条边之间最短路cnt,转化为原三元组的期望,ans=cnt*(n-2)/C(n,3)=cnt*6/n/(n-1)
求两两之间的最短路，先建树，对于每个结点，其父边需要走的次数等于其子孙(包括自己)个数*其他节点个数
(在边两边的节点之间的最短路一定经过该边)
处理出该信息后，结合每条边长度即求出cnt,即可求出ans
每次减少边长度,使用预处理信息动态减少cnt即可
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long LL;
const int MAXN = 200110;

/*io优化 */
inline int readint()
{
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

/*建无向图*/
int n, m;
int g[MAXN], to[MAXN], len[MAXN], nextn[MAXN], eid = 0;
void addedge(int x, int y, int z)
{
    to[++eid] = y, len[eid] = z, nextn[eid] = g[x], g[x] = eid;
    to[++eid] = x, len[eid] = z, nextn[eid] = g[y], g[y] = eid;
}

/*建树*/
int depth[MAXN], fa[MAXN]; //fa[x]表示第x个节点的祖先，不存在用0表示
int sonsum[MAXN];          //sonsum[x]表示x结点的包括x自己的子孙数量
int nodetoid[MAXN];        //将点的序号对应到边的序号
LL idsums[MAXN];           //第x条边需要重复走的次数

void dfs(int nfa, int nu) //以nu为根的子树，其父节点为nfa
{
    //printf("nfa=%d nu=%d\n",nfa,nu);
    if (nfa != 0)
        depth[nu] = depth[nfa] + 1; //树的逻辑深度
    else
        depth[nu] = 1;
    fa[nu] = nfa;
    sonsum[nu] = 1; //子孙数量先包含自己
    for (int i = g[nu]; i != -1; i = nextn[i])
    {
        if (to[i] != nfa)
        {
            nodetoid[to[i]] = (i + 1) / 2;
            dfs(nu, to[i]);
            sonsum[nu] += sonsum[to[i]];
        }
    }
}
void buildtree(int root)
{
    memset(fa, 0, sizeof(fa));
    memset(depth, 0, sizeof(depth));
    memset(sonsum, 0, sizeof(sonsum));
    dfs(0, root);
}

int main()
{
    n = readint();
    int u, v, c;
    memset(nextn, -1, sizeof(nextn));
    memset(g, -1, sizeof(g));

    for (int i = 1; i < n; i++)
    {
        u = readint(), v = readint(), c = readint();
        addedge(u, v, c);
    }
    buildtree(1);
    double ans = 0, cmn;
    cmn = 6. / n / (n - 1);
    for (int i = 2; i <= n; i++)
    {
        idsums[nodetoid[i]] = (long long)sonsum[i] * (n - sonsum[i]);
        ans += idsums[nodetoid[i]] * len[nodetoid[i] * 2];
    }
    m = readint();
    for (int i = 1; i <= m; i++)
    {
        u = readint(), v = readint();
        ans -= (len[2 * u] - v) * idsums[u];
        len[2 * u] = v;
        printf("%.9f\n", ans * cmn);
    }
    return 0;
}