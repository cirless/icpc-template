### Problem Description

Years later, Jerry fell in love with a girl, and he often walks for a long time to pay visits to her. But, because he spends too much time with his girlfriend, Tom feels neglected and wants to prevent him from visiting her.

After doing some research on the neighbourhood, Tom found that the neighbourhood consists of exactly n houses, and some of them are connected with directed road. To visit his girlfriend, Jerry needs to start from his house indexed 1 and go along the shortest path to hers, indexed n.

Now Tom wants to block some of the roads so that Jerry has to walk longer to reach his girl's home, and he found that the cost of blocking a road equals to its length. 

Now he wants to know the minimum total cost to make Jerry walk longer.

Note, if Jerry can't reach his girl's house in the very beginning, the answer is obviously zero. And you don't need to guarantee that there still exists a way from Jerry's house to his girl's after blocking some edges.


### Input
The input begins with a line containing one integer $T(1≤T≤10)$ , the number of test cases.

Each test case starts with a line containing two numbers $n,m(1≤n,m≤10000)$ , the number of houses and the number of one-way roads in the neighbourhood.

m lines follow, each of which consists of three integers $x,y,c(1≤x,y≤n,1≤c≤10^9)$, denoting that there exists a one-way road from the house indexed $x$ to $y$ of length $c$.
 

### Output
Print $T$ lines, each line containing a integer, the answer.
 

### Sample Input
```
1
3 4
1 2 1
2 3 1
1 3 2
1 3 3
```

### Sample Output
```
3
```

### 题目大意
给定一张n个点，m条边的带权有向图，考察从结点1到结点n的最短路。减去图的一些边，减边的代价为该边的边权。要求以最小的代价减去一些边，使从结点1到结点n的最短路变长，求最小的代价

### 算法思路
先使用Dijkstra算法求出最短路，然后依照以下方法构造最短路图
``` cpp
if(dis[u[i]]+w[i] == dis[v[i]]){
    addEdge(u[i],v[i],w[i]);
}
```
其中dis[i]表示第1个点到第i个点的距离，u[i],v[i],w[i]分别为起点，终点，边权

之后求这张最短路图的最小割，根据最大流最小割定理，使用Dinic算法跑一遍最大流即可