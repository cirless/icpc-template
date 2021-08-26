/* source: https://acm.hdu.edu.cn/showproblem.php?pid=6582
一个图论母题，包含了最短路径和最小割问题，使用 Dijkstra、Dinic算法
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef long long ll;

const long long maxn = 10010;

struct node {
    long long v, w;
    node(long long v = 0, long long w = 0) : v(v), w(w){};
    inline bool operator<(const node& a) const { return w > a.w; }
};

vector<node> G[maxn];
ll dis[maxn];
bool vis[maxn];
long long u[maxn], v[maxn], w[maxn];

inline void add(long long u, long long v, long long w) {
    G[u].push_back(node(v, w));
}

void init() {
    for (long long i = 0; i < maxn; i++) {
        G[i].clear();
        vis[i] = false;
        dis[i] = 1e18;
    }
}

void dijkstra(long long s) {
    priority_queue<node> Q;
    Q.push(node(s, 0));
    dis[s] = 0;
    while (!Q.empty()) {
        node now = Q.top();
        Q.pop();
        long long v = now.v;
        if (vis[v])
            continue;
        vis[v] = true;
        for (node i : G[v]) {
            long long v2 = i.v;
            long long len = i.w;
            if (!vis[v2] && dis[v2] > dis[v] + len) {
                dis[v2] = dis[v] + len;
                Q.push(node(v2, dis[v2]));
            }
        }
    }
}

struct Edge {
    long long to, cap;
    Edge(long long to, long long cap) : to(to), cap(cap) {}
};

struct Dinic {
    const long long INF = 1e18;
    long long n, s, t;
    vector<Edge> es;
    vector<vector<long long> > G;
    vector<long long> dis, cur;
    Dinic(long long n, long long s, long long t) : n(n), s(s), t(t), G(n + 1), dis(n + 1), cur(n + 1) {}

    void addEdge(long long u, long long v, long long cap) {
        G[u].push_back(es.size());
        es.emplace_back(v, cap);
        G[v].push_back(es.size());
        es.emplace_back(u, 0);
    }

    bool bfs() {
        dis.assign(n + 1, 0);
        queue<long long> q;
        q.push(s);
        dis[s] = 1;
        while (!q.empty()) {
            long long u = q.front();
            q.pop();
            for (long long i : G[u]) {
                Edge& e = es[i];
                if (!dis[e.to] && e.cap > 0) {
                    dis[e.to] = dis[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return dis[t];
    }

    long long dfs(long long u, long long cap) {
        if (u == t || cap == 0)
            return cap;
        long long tmp = cap, f;
        for (long long& i = cur[u]; i < G[u].size(); i++) {
            Edge& e = es[G[u][i]];
            if (dis[e.to] == dis[u] + 1) {
                f = dfs(e.to, min(cap, e.cap));
                e.cap -= f;
                es[G[u][i] ^ 1].cap += f;
                cap -= f;
                if (cap == 0)
                    break;
            }
        }
        return tmp - cap;
    }

    ll solve() {
        ll flow = 0;
        while (bfs()) {
            cur.assign(n + 1, 0);
            flow += dfs(s, INF);
        }
        return flow;
    }
};

int main() {
    long long t;
    cin >> t;
    while (t-- > 0) {
        long long n, m;
        cin >> n >> m;
        init();
        for (long long i = 1; i <= m; i++) {
            cin >> u[i] >> v[i] >> w[i];
            add(u[i], v[i], w[i]);
        }
        dijkstra(1);
        Dinic dinic = Dinic(n, 1, n);
        for (long long i = 1; i <= m; i++) {
            if (dis[u[i]] + w[i] == dis[v[i]]) {
                dinic.addEdge(u[i], v[i], w[i]);
            }
        }
        cout << dinic.solve() << endl;
    }
    return 0;
}