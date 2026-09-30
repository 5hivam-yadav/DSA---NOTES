#include <bits/stdc++.h>
using namespace std;

class FenwickTree {
    vector<long long> bit;

  public:
    explicit FenwickTree(int n) : bit(n + 1, 0) {}

    // Add delta at zero-based index i.
    void add(int i, long long delta) {
        for (++i; i < (int)bit.size(); i += i & -i)
            bit[i] += delta;
    }

    // Sum over the half-open prefix [0, end).
    long long prefixSum(int end) const {
        long long sum = 0;
        for (int i = end; i > 0; i -= i & -i)
            sum += bit[i];
        return sum;
    }

    // Sum over [left, right).
    long long rangeSum(int left, int right) const {
        return prefixSum(right) - prefixSum(left);
    }
};
