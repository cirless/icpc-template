/* source: https://www.luogu.com.cn/problem/P4779
配对堆优化的Dijkstra算法求最短路
同时配合读入优化
*/
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;
typedef long long LL;
typedef __gnu_pbds::priority_queue<pair<int, int>, greater<pair<int, int>>, pairing_heap_tag> heap;

/*读入优化*/
class Scanner {
    static constexpr int BUF_SIZE = 1048576;  // 1MB
    char buf[BUF_SIZE], *p1 = buf, *p2 = buf;

    char nc() {
        if (p1 == p2) {
            p1 = buf;
            p2 = buf + fread(buf, 1, BUF_SIZE, stdin);
            // assert(p1 != p2);
        }
        return *p1++;
    }

   public:
    int nextInt() {
        int x = 0, sgn = 1;
        char c = nc();
        for (; c < '0' || c > '9'; c = nc())
            if (c == '-') sgn = -1;
        for (; c >= '0' && c <= '9'; c = nc()) x = x * 10 + (c - '0');
        return sgn * x;
    }

    double nextDouble() {
        double x = 0, base = 0.1;
        int sgn = 1;
        char c = nc();
        for (; c < '0' || c > '9'; c = nc())
            if (c == '-') sgn = -1;
        for (; c >= '0' && c <= '9'; c = nc()) x = x * 10 + (c - '0');
        for (; c < '0' || c > '9'; c = nc())
            if (c != '.') return sgn * x;
        for (; c >= '0' && c <= '9'; c = nc())
            x += base * (c - '0'), base *= 0.1;
        return sgn * x;
    }
} in;

const int MAXN = 100010, MAXM = 500010, inf = 2147483647;

int n, m, s;

int g[MAXN], to[MAXM], len[MAXM], nextn[MAXM], eid;
heap q1;
heap::point_const_iterator id[MAXN];

void addedge(int a, int b, int c) {
    to[++eid] = b, len[eid] = c, nextn[eid] = g[a], g[a] = eid;
}

int dist[MAXN];
void dij(int yuan) {
    for (int i = 1; i <= n; i++) dist[i] = inf;  //题目要求初始化为1<<31-1
    dist[yuan] = 0;
    id[yuan] = q1.push(make_pair(0, yuan));
    while (!q1.empty()) {
        int t = q1.top().second, len1 = q1.top().first, len2;
        q1.pop();
        for (int i = g[t]; i != -1; i = nextn[i]) {
            len2 = len1 + len[i];
            if (len2 < dist[to[i]]) {
                dist[to[i]] = len2;
                if (id[to[i]] != 0)
                    q1.modify(id[to[i]], make_pair(dist[to[i]], to[i]));
                else
                    id[to[i]] = q1.push(make_pair(dist[to[i]], to[i]));
            }
        }
    }
}
int main()
{
    memset(g, -1, sizeof(g));
    memset(nextn, -1, sizeof(nextn));
    memset(to, -1, sizeof(to));

    //scanf("%d%d%d", &n, &m, &s);
    //n=readint();m=readint();s=readint();
    n=in.nextInt();m=in.nextInt();s=in.nextInt();
    for (int i = 1; i <= m; i++)
    {
        int x, y, z;
        //scanf("%d%d%d", &x, &y, &z);
        //x=readint();y=readint();z=readint();
        x=in.nextInt();y=in.nextInt();z=in.nextInt();
        addedge(x, y, z);
    }
    dij(s);
    for (int i = 1; i <= n; i++)
    {
        //print(dist[i]);putchar(' ');
        printf("%d ", dist[i]);
    }    
    return 0;
}