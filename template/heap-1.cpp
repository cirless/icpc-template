// 二叉堆，可用于优先队列的维护
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename Data>
class Heap {
#define fa(x) ((x - 1) >> 1)
#define lc(x) (((x) << 1) + 1)
#define rc(x) (((x) << 1) + 2)
// 比较函数，<时为大根堆
#define _cmp(a, b) ((a) > (b))
   private:
    vector<Data> nums;
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
    Heap() {}
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
#undef _cmp
};

int main() {
    Heap<int> minHeap;
    minHeap.push(3);
    minHeap.push(2);
    minHeap.push(1);
    cout << minHeap.top() << endl;
    minHeap.pop();
    cout << minHeap.top() << endl;
    minHeap.pop();

    cout << minHeap.top() << endl;
}