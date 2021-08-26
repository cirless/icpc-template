// 取最高位（int下）
unsigned upbit(unsigned x) {
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);
    return (x + 1) >> 1;
}
unsigned long long upbit(unsigned long long x) {
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);
    x = x | (x >> 32);
    return (x + 1) >> 1;
}
// 取最低位
int lowbit(int n) { return n & (-n); }
// 求不小于它的最小的2的幂
unsigned clp2(unsigned x) {
    x = x - 1;
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >> 16);
    return x + 1;
}
// 二进制中1的个数
int NumberOf1(int n) {
    //把一个整数减去1，再与原整数相与，会把原整数的最右边的1变成0
    int cnt = 0;
    while (n) {
        cnt++;
        n = n & (n - 1);
    }
    return cnt;
}