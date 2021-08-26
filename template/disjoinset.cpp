/*并查集模板，主要对例题t006进行了封装
包含查询和合并2个操作
*/
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct DisjointSet {
    vector<int> fa;
    int num;
    // 参数n为并查集的初始元素总数
    DisjointSet(int n) : fa(n + 5) {
        this->num = n;
        for (int i = 1; i <= n; i++) {
            fa[i] = i;
        }
    }
    int findfa(int x) {
        if (fa[x] != x)
            return findfa(fa[x]);
        else
            return x;
    }
    // 判断是否在一个集合内
    bool iscon(int x, int y) {
        if (findfa(x) == findfa(y))
            return true;
        return false;
    }
    // 合并2个集合
    void merge(int x, int y) { fa[findfa(x)] = findfa(y); }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int x, y, z;
    DisjointSet dset(n);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &z, &x, &y);
        if (z == 1) {
            dset.merge(x, y);
        } else {
            if (dset.iscon(x, y))
                printf("Y\n");
            else
                printf("N\n");
        }
    }
    return 0;
}