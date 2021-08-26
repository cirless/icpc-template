### Problem Description

A and B are preparing themselves for programming contests.

The University where A and B study is a set of rooms connected by corridors. Overall, the University has n rooms connected by $n-1$ corridors so that you can get from any room to any other one by moving along the corridors. The rooms are numbered from $1$ to $n$.

Every day А and B write contests in some rooms of their university, and after each contest they gather together in the same room and discuss problems. A and B want the distance from the rooms where problems are discussed to the rooms where contests are written to be equal. The distance between two rooms is the number of edges on the shortest path between them.

As they write contests in new rooms every day, they asked you to help them find the number of possible rooms to discuss problems for each of the following $m$ days.

### Input
The first line contains integer $n (1 ≤ n ≤ 10^5)$ — the number of rooms in the University.

The next $n-1$ lines describe the corridors. The i-th of these lines $(1 ≤ i ≤ n - 1)$ contains two integers $a_i$ and $b_i$ $(1 ≤ a_i, b_i ≤ n)$ , showing that the $i$-th corridor connects rooms $a_i$ and $b_i$.

The next line contains integer $m (1 ≤ m ≤ 10^5)$ — the number of queries.

Next m lines describe the queries. The j-th of these lines $(1 ≤ j ≤ m)$ contains two integers $x_j$ and $y_j$ $(1 ≤ x_j, y_j ≤ n)$ that means that on the $j$-th day A will write the contest in the room $x_j$, B will write in the room $y_j$.

### Output
In the $i$-th $(1 ≤ i ≤ m)$ line print the number of rooms that are equidistant from the rooms where A and B write contest on the $i$-th day.

### Examples

#### input1
```
4
1 2
1 3
2 4
1
2 3
```
#### output1
```
1
```
#### input2
```
4
1 2
2 3
2 4
2
1 2
1 3
```
#### output2
```
0
2
```

### 题目大意
给定一棵有n个节点的无根树和q个询问Query(x,y)，每个询问求出树上到x,y两节点距离相等的节点个数。

### 算法思路
为方便后续计算，先指定一个度数最大的结点为根root，并以此确定树的方向。

使用倍增的思想实现LCA最近公共祖先算法，通过O(nlogn)的复杂度进行了树的预处理，得到每节点的祖先数据，之后每一次询问两节点的LCA都是O(logn)复杂度的。

易知树上任意两点间有且只有一条简单路径，对于任意两节点，到它们两节点距离相等的有且只有其路径中点及该中点所连的不在原路径上的任意节点。

因此，使用树形dp的思路。考虑已转化为有根树，统计每个节点对应子树中的结点个数备用。

对于x,y中点是它们的LCA的情况，答案点集就是整棵树砍掉以两点为根的两棵子树。

对于x,y中点不是它们的LCA的情况，答案点集是“以中点为根的子树砍掉以中点在中点到询问点的路径上的儿子为根的子树”

总体复杂度$O((q+n)log \ n)$