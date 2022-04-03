// 二叉堆，可用于优先队列的维护
// 模板类参数中传入比较器类，实现大根堆和小根堆复用

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename Data, typename _Compare = less<Data>>
class Heap {
#define fa(x) ((x - 1) >> 1)
#define lc(x) (((x) << 1) + 1)
#define rc(x) (((x) << 1) + 2)

   protected:
    vector<Data> nums;
    _Compare _cmp;
    void upAdjust(int idx) {
        while (idx > 0 && _cmp(nums[fa(idx)], nums[idx])) {
            swap(nums[fa(idx)], nums[idx]);
            idx = fa(idx);
        }
    }
    void downAdjust(int idx) {
        while (lc(idx) < nums.size()) {
            int idchild = 0;
            if (rc(idx) < nums.size() && _cmp(nums[lc(idx)], nums[rc(idx)]))
                idchild = rc(idx);
            else
                idchild = lc(idx);
            if (_cmp(nums[idx], nums[idchild])) {
                swap(nums[idchild], nums[idx]);
                idx = idchild;
            } else {
                break;
            }
        }
    }

   public:
    Heap() { _cmp = _Compare(); }
    ~Heap() {}
    Data top() {
        if (nums.size() > 0)
            return nums[0];
        return -1;
    }

    void push(Data a) {
        nums.push_back(a);
        upAdjust(nums.size() - 1);
    }
    void pop() {
        if (nums.size() > 0) {
            swap(nums.front(), nums.back());
            nums.pop_back();
            downAdjust(0);
        }
    }
    size_t size() { return nums.size(); }

#undef fa
#undef lc
#undef rc
};

int main() {
    Heap<int, greater<int>> minHeap;
    minHeap.push(3);
    minHeap.push(2);
    minHeap.push(1);
    cout << minHeap.top() << endl;
    minHeap.pop();
    cout << minHeap.top() << endl;
    minHeap.pop();

    cout << minHeap.top() << endl;
}