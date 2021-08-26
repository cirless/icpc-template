/* source: https://acm.hdu.edu.cn/showproblem.php?pid=2087
 *KMP算法，一种在线性时间内进行单模式串匹配的方法
 */
#include <cstdio>
#include <cstring>
char a[1010], b[1010];
int la, lb, next[1010];
void getnext(char* s, int l) {
    memset(next, 0, sizeof(next));
    next[0] = -1;  // nextn[0]初始化为-1，-1表示不存在相同的最大前缀和最大后缀
    for (int i = 1, j = -1; i < l; i++) {
        while (j > -1 && s[i] != s[j + 1])
            j = next[j];       //如果下一位不匹配，那么回溯
        if (s[i] == s[j + 1])  //如果这位匹配上了，那么串b的指针j移到这一位
            j++;
        next[i] = j;
    }
}
int kmp(char* a, char* b, int la, int lb) {
    int ans = 0;
    getnext(b, lb);
    for (int i = 0, j = -1; i < la; i++) {
        while (j > -1 && a[i] != b[j + 1])
            j = next[j];//这位不匹配，且j>-1，即仍有部分匹配，向前回溯 
        if (a[i] == b[j + 1])
            j++;
        if (j == (lb - 1)) {
            // 匹配到一个子串
            ans++;
            j = -1;
        }
    }
    return ans;
}

int main() {
    while (scanf("%s", a)) {
        if (a[0] == '#')
            break;
        scanf("%s", b);
        la = strlen(a), lb = strlen(b);
        int ans = kmp(a, b, la, lb);
        printf("%d\n", ans);
    }
    return 0;
}
