#include <bits/stdc++.h>
using namespace std;

void siftDown(vector<int> &values, int size, int root) {
    while (true) {
        int largest = root;
        int left = 2 * root + 1;
        int right = left + 1;
        if (left < size && values[left] > values[largest])
            largest = left;
        if (right < size && values[right] > values[largest])
            largest = right;
        if (largest == root)
            return;
        swap(values[root], values[largest]);
        root = largest;
    }
}

void heapSort(vector<int> &values) {
    int n = values.size();
    for (int root = n / 2 - 1; root >= 0; --root)
        siftDown(values, n, root);
    for (int end = n - 1; end > 0; --end) {
        swap(values[0], values[end]);
        siftDown(values, end, 0);
    }
}
