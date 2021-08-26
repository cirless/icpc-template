/*
非旋转的treap平衡树模板
可以稳定地维护一个二叉平衡搜索树，其查询第k大的时间复杂度为O(n)
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 100010;
namespace Treap {
int num;
struct Node {
    int data, key, sz;
    int ls, rs;
    Node(){};
    Node(int data, int key, int sz, int ls = 0, int rs = 0) : data(data), key(key), sz(sz), ls(ls), rs(rs){};
} T[maxn];
void pushup(int x) {
    T[x].sz = T[T[x].ls].sz + T[T[x].rs].sz + 1;
}
int newnode(int x) {
    T[++num] = Node(x, rand(), 1);
    return num;
}
int merge(int x, int y) {
    if (!x || !y)
        return x + y;
    if (T[x].key < T[y].key) {
        T[x].rs = merge(T[x].rs, y);
        pushup(x);
        return x;
    } else {
        T[y].ls = merge(x, T[y].ls);
        pushup(y);
        return y;
    }
}
void split(int now, int k, int& x, int& y) {
    if (!now) {
        x = y = 0;
        return;
    }

    if (T[now].data <= k)
        x = now, split(T[now].rs, k, T[now].rs, y);
    else
        y = now, split(T[now].ls, k, x, T[now].ls);
    pushup(now);
}
int kth(int now, int k) {
    while (1) {
        if (k <= T[T[now].ls].sz)
            now = T[now].ls;
        else if (k == T[T[now].ls].sz + 1)
            return now;
        else
            k -= T[T[now].ls].sz + 1, now = T[now].rs;
    }
}
}  // namespace Treap
using namespace Treap;

namespace Treap_with_point {
struct node {
    node* ch[2];
    int data, key, sz, flip;
    int siz(int x) {
        if (ch[x] != NULL)
            return ch[x]->sz;
        else
            return 0;
    }
    void pushdown() {
        if (flip) {
            flip = 0;
            swap(ch[0], ch[1]);
            if (ch[0] != NULL)
                ch[0]->flip ^= 1;
            if (ch[1] != NULL)
                ch[1]->flip ^= 1;
        }
    }
    void maintain() { sz = 1 + siz(0) + siz(1); }
} * root;
typedef pair<node*, node*> droot;
node* merge(node* a, node* b) {
    if (a == NULL)
        return b;
    if (b == NULL)
        return a;
    a->pushdown();
    b->pushdown();
    if (a->key < b->key) {
        a->ch[1] = merge(a->ch[1], b);
        a->maintain();
        return a;
    } else {
        b->ch[0] = merge(a, b->ch[0]);
        b->maintain();
        return b;
    }
}
droot split(node* a, int k) {
    if (a == NULL)
        return droot(NULL, NULL);
    droot ret;
    a->pushdown();
    if (a->siz(0) >= k) {
        ret = split(a->ch[0], k);
        a->ch[0] = ret.second;
        a->maintain();
        ret.second = a;
    } else {
        ret = split(a->ch[1], k - a->siz(0) - 1);
        a->ch[1] = ret.first;
        a->maintain();
        ret.first = a;
    }
    return ret;
}
void insert(int x) {
    node* t = new node;
    t->data = x;
    t->key = rand();
    t->sz = 1;
    t->flip = 0;
    t->ch[0] = t->ch[1] = NULL;
    root = merge(root, t);
}
void output(node* o) {
    if (!o)
        return;
    o->pushdown();
    if (o->ch[0])
        output(o->ch[0]);
    printf("%d ", o->data);
    if (o->ch[1])
        output(o->ch[1]);
}
}