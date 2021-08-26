/*
图论模板，主要对例题t010进行了封装
使用面向对象的设计将边上所带数据data、边edge、有向图graph和Dijkstra算法分别封装为class，并相互结合
极大地避免了原程序中全局变量过多的弊端，也能方便地修改数据类型
同时复用性大大提高，模板代码不再需要针对各种情况修改，只需要在main函数中构造对象时输入参数即可
*/

#include <algorithm>
#include <cstdio>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef long long ll;

typedef __gnu_pbds::priority_queue<pair<ll, int>, greater<pair<ll, int>>, __gnu_pbds::pairing_heap_tag> heap;

// 边上所带的信息
struct edgeData {
    ll w;
    edgeData(ll w = 0) : w(w){};
    bool operator<(const edgeData& a) const { return w < a.w; }
    bool operator==(const edgeData& a) const { return w == a.w; }
    bool operator>(const edgeData& a) const { return w > a.w; }
};
// 一条有向边的结点
struct edge {
    int to;         // to为该边终点
    edgeData data;  // w为边上所带的信息
    edge(int to = 0, edgeData data = edgeData()) : to(to), data(data){};
    bool operator<(const edge& a) const { return data > a.data; }
};

// 一个在构造对象时已确定图的结点数量的Graph类
class Graph {
   private:
    int nodenum = 0;
    vector<vector<edge>> G;

   public:
    // 必要的参数为图中的结点数，基于此初始化图
    Graph(int nodenum) : nodenum(nodenum) { G.resize(nodenum + 5); }

    // 添加一条边，从fr到to，权值为w
    void addEdge(ll fr, ll to, edgeData data) { G[fr].push_back(edge(to, data)); }

    // 重载了[]运算符，便于调取图中的邻接表的数据
    vector<edge>& operator[](size_t i) { return G[i]; }

    // 图的结点数
    size_t size() { return nodenum; }
};

struct Dijkstra {
    const ll INF;
    Graph G;
    ll source_node;
    vector<ll> dist;
    void run() {
        // 初始化一些中间变量数组
        vector<bool> vis(G.size() + 5, false);
        vector<heap::point_const_iterator> id(G.size() + 5, 0);
        dist.clear();
        // 将距离初始化为无穷大
        dist.resize(G.size() + 5, INF);

        heap q1;
        dist[source_node] = 0LL;
        q1.push(make_pair(0LL, source_node));
        while (!q1.empty()) {
            int nu = q1.top().second;
            ll len1 = q1.top().first, len2;
            q1.pop();
            // Dijkstra的松弛过程
            for (auto e : G[nu]) {
                len2 = len1 + (ll)e.data.w;
                if (dist[e.to] > len2) {
                    dist[e.to] = len2;
                    if (id[e.to] != 0)
                        q1.modify(id[e.to], make_pair(dist[e.to], e.to));
                    else
                        id[e.to] = q1.push(make_pair(dist[e.to], e.to));
                }
            }
        }
    }
    // 构造时输入一个图，并指定计算最短路的源点
    Dijkstra(Graph g, ll source_node, ll inf = 1e18) : G(g), source_node(source_node), INF(inf) { run(); }

    // 也可以修改源点，重新计算最短路
    void change_source(ll s) {
        if (s < G.size()) {
            source_node = s;
            run();
        }
    }
};

int main() {
    int n, m, s;
    scanf("%d%d%d", &n, &m, &s);
    // 构造有向图的对象
    Graph g(n);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        g.addEdge(x, y, z);
    }
    // 构造Dijkstra算法处理器的对象
    Dijkstra dij(g, s, 2147483647);
    for (int i = 1; i <= n; i++)
        printf("%d ", dij.dist[i]);
}