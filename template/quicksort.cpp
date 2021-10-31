#include <cstdio>
#include <cstring>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

typedef long long ll;

pair<int, int> findPivot(vector<int>& A, int lo, int hi) {
    int i = lo, j = lo, k = lo;
    // [lo, i) <
    // [i, j)  ==
    // [j, k)  >
    // [k, hi) unknown
    swap(A[lo], A[lo + (rand()) % (hi - lo)]);
    int pivot = A[lo];

    while (k < hi) {
        if (A[k] > pivot) {
            k++;
        } else if (A[k] == pivot) {
            swap(A[k], A[j]);
            k++;
            j++;
        } else {
            swap(A[k], A[j]);
            swap(A[j], A[i]);
            i++;
            j++;
            k++;
        }
    }
    return {i, j};
}

void quickSort(vector<int>& nums, int lo, int hi) {
    if (hi - lo < 2)
        return;
    auto [mi1, mi2] = findPivot(nums, lo, hi);
    quickSort(nums, lo, mi1);
    quickSort(nums, mi2, hi);
}
