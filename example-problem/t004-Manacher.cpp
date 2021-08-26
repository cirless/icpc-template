/* source: https://codeforces.com/gym/102448/problem/A
马拉车算法，一种查找一个字符串的最长回文子串的线性方法
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;
const int maxn = 5e5 + 5;

int n, m, p[maxn * 2];
char s[maxn], s2[maxn * 2];
/*预处理字符串和生成p数组*/
void mlc() {
    int l2 = 0;
    for (int i = 0; i < n; i++) {
        s2[l2++] = '#';
        s2[l2++] = s[i];
    }
    s2[l2++] = '#';

    // 双指针，它们是一一对应的，须同时更新
    int maxRight = 0;
    int center = 0;

    // 当前遍历的中心最大扩散步数，其值等于原始字符串的最长回文子串的长度
    int maxLen = 1;
    // 原始字符串的最长回文子串的起始位置，与 maxLen 必须同时更新
    int start = 0;

    for (int i = 0; i < l2; i++) {
        if (i < maxRight) {
            int mirror = 2 * center - i;
            // 这一行代码是 Manacher 算法的关键所在，要结合图形来理解
            p[i] = min(maxRight - i, p[mirror]);
        }

        // 下一次尝试扩散的左右起点，能扩散的步数直接加到 p[i] 中
        int left = i - (1 + p[i]);
        int right = i + (1 + p[i]);

        // left >= 0 && right < l2 保证不越界
        // str.charAt(left) == str.charAt(right) 表示可以扩散 1 次
        while (left >= 0 && right < l2 && s2[left] == s2[right]) {
            p[i]++;
            left--;
            right++;
        }
        // 根据 maxRight 的定义，它是遍历过的 i 的 i + p[i] 的最大者
        // 如果 maxRight 的值越大，进入上面 i < maxRight
        // 的判断的可能性就越大，这样就可以重复利用之前判断过的回文信息了
        if (i + p[i] > maxRight) {
            // maxRight 和 center 需要同时更新
            maxRight = i + p[i];
            center = i;
        }
        if (p[i] > maxLen) {
            // 记录最长回文子串的长度和相应它在原始字符串中的起点
            maxLen = p[i];
            start = (i - maxLen) / 2;
        }
    }
}
bool pd() {
    // 特判
    if (n < 2) {
        return true;
    }
    mlc();
    int l2 = 2 * n + 1;
    for (int i = 1; i < l2; i++) {
        if (p[i] >= m && (p[i] % 2) == (m % 2))
            return true;
    }
    return false;
}

int main() {
    scanf("%d%d", &n, &m);
    scanf("%s", s);
    if (pd()) {
        printf("Accept");
    } else {
        printf("Reject");
    }
    return 0;
}