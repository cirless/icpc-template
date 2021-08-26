## Accept or Reject
### Problem Description
This semester, various UFPE competitors had classes of a discipline called Theoretical Informatics. One of the major studied concepts was **Turing Machines (TM)**.

A **TM** is basically a system that has a tape with infinite memory cells to the right and a head pointer that is always pointing to one cell at a given moment.

A known fact in computer science is that every algorithm has an equivalent **TM**.

There are many **TM** variations and some of them has capability differences. One of these variations are the Deciders, which are machines that always stops (never entering infinite loop state), "accepting" or "rejecting" any given input.

One of the recommended exercises of the discipline was the following: "Describe a Decider that accepts a given input string of size N if it has an M sized palindrome as substring and reject if not".

Your task here is to solve this exercise, but as we do not have compilers that can interpret **TM** descriptions, you instead has to code an equivalent algorithm to solve it.

### Input
The input will contain only one test set. You will receive two integers $N$ and $M (1≤M≤N≤5⋅10^5)$, as described above, followed by a line with a string $S$ of size $N$. It is guaranteed that $S$ contains only lowercase english letters.

### Output
The output must contain only one line with "Accept" (without quotes) if your **Decider** accepts the input or "Reject" (without quotes) if it doesn't.

You may print every letter in any case you want (so, for example, the strings Accept, accept, ACcept and accEpT will all be recognized as a positive answer).

### Examples

#### input1
```
10 4
ajabbaaksj
```
#### output1
```
Accept
```
#### input2
```
10 5
ajabbaaksj
```
#### output2
```
Reject
```

### 题目大意
给定一个长度为n的字符串，判断里面是否有长度为m的回文串

### 算法思路
使用马拉车算法(Manacher‘s Algorithm)，进行预处理后得出字符串中以每个字符为中心的回文半径，然后遍历一遍判断其中是否有长度为m的即可。