### Problem Description
给定一个 n 个点，m 条有向边的带非负权图，请你计算从 s 出发，到每个点的距离。
数据保证你能从 s 出发到任意点。

### Input
第一行为三个正整数 $n, m, s$。 第二行起 m 行，每行三个非负整数 $u_i, v_i, w_i$​，表示从 $u_i​$ 到 $v_i$ 有一条权值为 $w_i​$ 的有向边。

$1\leq n\leq 10^5$
$1 \leq m \leq 2\times 10^5$
$s = 1$
$1 \leq u_i, v_i\leq n$
$0 \leq w_i \leq 10 ^ 9$
$0 \leq \sum w_i \leq 10 ^ 9$

### Output
输出一行 $n$ 个空格分隔的非负整数，表示 $s$ 到每个点的距离。
### Examples

#### input1
```
4 6 1
1 2 2
2 3 2
2 4 1
1 3 5
3 4 3
1 4 4
```
#### output1
```
0 2 4 3
```


### 算法思路
裸题，使用配对堆高效维护带修改操作的优先队列，进行Dijkstra算法即可