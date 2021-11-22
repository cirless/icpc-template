#include <cstdio>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

// 表达式中的元素类型，包含了数值和符号
struct Node {
    bool state;  // 0 is op, 1 is num
    double num;
    char op;
    Node(double num) : state(1), num(num), op('\0') {}
    Node(char op) : state(0), num(0.0), op(op) {}
};

// 字符的优先级，包括数字、四则运算符和括号
int getpriority(char c) {
    if (c >= '0' && c <= '9') return 0;
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '(') return 3;
    if (c == ')') return 4;
    return -1;
}
// 计算后缀表达式的值
double culExpVector(vector<Node> &v) {
    double ans = 0.0, n1, n2, num;
    stack<double> numstack;
    for (auto &i : v) {
        if (i.state == 1) {
            numstack.push(i.num);
        } else {
            n2 = numstack.top();
            numstack.pop();
            n1 = numstack.top();
            numstack.pop();
            if (i.op == '+') {
                num = n1 + n2;
            } else if (i.op == '-') {
                num = n1 - n2;
            } else if (i.op == '*') {
                num = n1 * n2;
            } else if (i.op == '/') {
                num = n1 / n2;
            }
            numstack.push(num);
        }
    }
    ans = numstack.top();
    numstack.pop();
    return ans;
}
// 将一个含有整数 + - * / ( )的中缀表达式字符串解析，生成后缀表达式，并计算其值
double culExp(const string &s) {
    vector<Node> RPN;    //生成的后缀表达式
    stack<char> ops;     //符号栈
    int laststate = -1;  // 0 is op, 1 is num
    double num = 0.0;
    for (auto i : s) {
        if ((i >= '0' && i <= '9')) {
            if (laststate == 1) {
                num = num * 10.0 + (i - '0');
            } else if (laststate == -1 || laststate == 0) {
                num = (double)(i - '0');
            }
            laststate = 1;
        } else {
            if (laststate == 1) {
                RPN.push_back(Node(num));
            }
            if (ops.empty()) {
                ops.push(i);
            } else {
                int prinum = getpriority(i);
                if (prinum == 3) {
                    ops.push(i);
                } else if (prinum == 4) {
                    while (!ops.empty()) {
                        if (ops.top() != '(') {
                            RPN.push_back(Node(ops.top()));
                            ops.pop();
                        } else {
                            ops.pop();
                            break;
                        }
                    }
                } else {
                    while (!ops.empty()) {
                        if (ops.top() == '(') {
                            break;
                        }
                        if (getpriority(ops.top()) >= prinum) {
                            RPN.push_back(Node(ops.top()));
                            ops.pop();
                        } else {
                            break;
                        }
                    }
                    ops.push(i);
                }
            }
            laststate = 0;
        }
    }
    if (laststate == 1) {
        RPN.push_back(Node(num));
    }
    while (!ops.empty()) {
        RPN.push_back(Node(ops.top()));
        ops.pop();
    }
    return culExpVector(RPN);
}

int main() {
    cout << culExp("12+34-56/67") << endl;
    cout << culExp("9+(3-1)*3+10/2") << endl;
    cout << culExp("9+(3-1)*3+(10/2)") << endl;
}
