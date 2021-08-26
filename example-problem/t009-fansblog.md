### Problem Description
Farmer John keeps a website called ‘FansBlog’ .Everyday , there are many people visited this blog.One day, he find the visits has reached $P$ , which is a prime number.He thinks it is a interesting fact.And he remembers that the visits had reached another prime number.He try to find out the largest prime number $Q ( Q < P )$ ,and get the answer of $Q!$ Module P.But he is too busy to find out the answer. So he ask you for help. ( $Q!$ is the product of all positive integers less than or equal to $n$: $n! = n * (n-1) * (n-2) * (n-3) *… * 3 * 2 * 1$ . For example, $4! = 4 * 3 * 2 * 1 = 24$ )

### Input
First line contains an number $T(1<=T<=10)$ indicating the number of testcases.
Then T line follows, each contains a positive prime number $P (1e9≤p≤1e14)$

### Output
For each testcase, output an integer representing the factorial of $Q$ modulo $P$.

### Examples

#### input1
```
1
1000000007
```
#### output1
```
328400734
```


### 题目大意
给定一个质数P (1e9≤p≤1e14),要求找到比P小但是和P的差最小的质数Q，求Q! mod P.

### 算法思路
由数论知识得质数分布规律：任意2000个自然数以内一定存在质数。
因此对于[P-1,P-2001]的区间的每一个数，判断它是否是质数，一旦找到质数则为Q
然后用Wilson定理计算答案
注意计算过程的数据可能很大，需要__int128