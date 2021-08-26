/*HDU4705
求一棵树上任取3点的三元组，使三个点不在一条简单路径上，即要经过他们必须走回头路
符合条件的三元组，（逻辑深度）中间点必然在最高点到最低点的路径上某点的子树上
逆而行之，先求C(n,3)，再减去在简单路径上的三元组的方案数即可
枚举中间点，取它两个子孙或一个子孙和除它所在子树其他任一点，都可以在简单路径上
用之前假题的dp1和dp2来维护，稍作改动即可
*/
#pragma comment(linker, "/STACK:16777216")
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include<vector>
using namespace std;
typedef long long LL;
const int MAXN = 100110;

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
int g[MAXN], to[MAXN*2], nextn[MAXN*2], eid = 0;
void addedge(int x, int y)
{
    to[++eid] = y, nextn[eid] = g[x], g[x] = eid;
    to[++eid] = x, nextn[eid] = g[y], g[y] = eid;
}

/*建树*/
int depth[MAXN], fa[MAXN]; //fa[x]表示第x个节点的祖先，不存在用0表示
int sonsum[MAXN];          //sonsum[x]表示x结点的包括x自己的子孙数量
LL dp1[MAXN],dp2[MAXN],dp3[MAXN],ans=0;

void dfs(int nfa, int nu) //以nu为根的子树，其父节点为nfa
{
    //printf("nfa=%d nu=%d\n",nfa,nu);
    if (nfa != 0)
        depth[nu] = depth[nfa] + 1; //树的逻辑深度
    else
        depth[nu] = 1;
    fa[nu] = nfa;
    dp1[nu] = 1; //子孙数量先包含自己
    LL sumdp1=0,sumdp2=0,sumsons=0;
    for (int i = g[nu]; i != -1; i = nextn[i])
    {
        if (to[i] != nfa)
        {
            sumsons++;
            dfs(nu, to[i]);
            dp1[nu] += dp1[to[i]];

            sumdp1+=dp1[to[i]];
            sumdp2+=dp2[to[i]];
        }
    }
    dp2[nu]=sumdp2;
    LL tem=0;
    for (int i = g[nu]; i != -1; i = nextn[i])
    {
        if (to[i] != nfa)
        {
            tem+=dp1[to[i]]*(sumdp1-dp1[to[i]]);
        }
    }
    dp2[nu]+=tem/2LL+(dp1[nu]-1)*(n-dp1[nu]);
}
void buildtree(int root)
{
    memset(fa, 0, sizeof(fa));
    memset(depth, 0, sizeof(depth));
    memset(sonsum, 0, sizeof(sonsum));
    memset(dp1,0,sizeof(dp1));
    memset(dp2,0,sizeof(dp2));
    memset(dp3,0,sizeof(dp3));
    
    dfs(0, root);
}

int main()
{
    while (scanf("%d", &n) != EOF && n != 0)
    {
        int u, v, c;
        memset(nextn, -1, sizeof(nextn));
        memset(g, -1, sizeof(g));
        eid=0;
        for (int i = 1; i < n; i++)
        {
            u = readint(), v = readint();
            addedge(u, v);
        }
        ans=(LL)n*(n-1)*(n-2)/6;
        buildtree(1);
        ans-=dp2[1];
        printf("%lld\n",ans);
    }
    return 0;
}