#include <bits/stdc++.h>
using namespace std;

class LazySegmentTree {
    int n;
    vector<long long> sum;
    vector<long long> lazy;

    void apply(int node, int left, int right, long long delta) {
        sum[node] += delta * (right - left);
        lazy[node] += delta;
    }

    void push(int node, int left, int right) {
        if (lazy[node] == 0 || right - left == 1)
            return;
        int mid = left + (right - left) / 2;
        apply(node * 2, left, mid, lazy[node]);
        apply(node * 2 + 1, mid, right, lazy[node]);
        lazy[node] = 0;
    }

    void add(int node, int left, int right, int ql, int qr, long long delta) {
        if (qr <= left || right <= ql)
            return;
        if (ql <= left && right <= qr) {
            apply(node, left, right, delta);
            return;
        }
        push(node, left, right);
        int mid = left + (right - left) / 2;
        add(node * 2, left, mid, ql, qr, delta);
        add(node * 2 + 1, mid, right, ql, qr, delta);
        sum[node] = sum[node * 2] + sum[node * 2 + 1];
    }

    long long query(int node, int left, int right, int ql, int qr) {
        if (qr <= left || right <= ql)
            return 0;
        if (ql <= left && right <= qr)
            return sum[node];
        push(node, left, right);
        int mid = left + (right - left) / 2;
        return query(node * 2, left, mid, ql, qr) +
               query(node * 2 + 1, mid, right, ql, qr);
    }

  public:
    explicit LazySegmentTree(int size)
        : n(size), sum(max(1, 4 * size), 0), lazy(max(1, 4 * size), 0) {}

    // Add delta to all elements in [left, right).
    void rangeAdd(int left, int right, long long delta) {
        if (left < 0 || right < left || right > n)
            throw out_of_range("range");
        if (left < right)
            add(1, 0, n, left, right, delta);
    }

    long long rangeSum(int left, int right) {
        if (left < 0 || right < left || right > n)
            throw out_of_range("range");
        if (left == right || n == 0)
            return 0;
        return query(1, 0, n, left, right);
    }
};
