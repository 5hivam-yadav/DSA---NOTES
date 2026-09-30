#include <bits/stdc++.h>
using namespace std;

class SegmentTreeSum {
    int n;
    vector<long long> tree;

    void build(int node, int left, int right, const vector<long long> &values) {
        if (right - left == 1) {
            tree[node] = values[left];
            return;
        }
        int mid = left + (right - left) / 2;
        build(node * 2, left, mid, values);
        build(node * 2 + 1, mid, right, values);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    void setValue(int node, int left, int right, int index, long long value) {
        if (right - left == 1) {
            tree[node] = value;
            return;
        }
        int mid = left + (right - left) / 2;
        if (index < mid)
            setValue(node * 2, left, mid, index, value);
        else
            setValue(node * 2 + 1, mid, right, index, value);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    long long query(int node, int left, int right, int ql, int qr) const {
        if (qr <= left || right <= ql)
            return 0;
        if (ql <= left && right <= qr)
            return tree[node];
        int mid = left + (right - left) / 2;
        return query(node * 2, left, mid, ql, qr) +
               query(node * 2 + 1, mid, right, ql, qr);
    }

  public:
    explicit SegmentTreeSum(const vector<long long> &values)
        : n(values.size()), tree(max(1, 4 * (int)values.size()), 0) {
        if (n > 0)
            build(1, 0, n, values);
    }

    void setValue(int index, long long value) {
        if (index < 0 || index >= n)
            throw out_of_range("index");
        setValue(1, 0, n, index, value);
    }

    // Sum over the half-open interval [left, right).
    long long rangeSum(int left, int right) const {
        if (left < 0 || right < left || right > n)
            throw out_of_range("range");
        return n == 0 ? 0 : query(1, 0, n, left, right);
    }
};
