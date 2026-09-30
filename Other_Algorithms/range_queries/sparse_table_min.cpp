#include <bits/stdc++.h>
using namespace std;

class SparseTableMin {
    vector<int> log2;
    vector<vector<int>> table;

  public:
    explicit SparseTableMin(const vector<int> &values) {
        int n = values.size();
        log2.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i)
            log2[i] = log2[i / 2] + 1;
        if (n == 0)
            return;
        table.assign(log2[n] + 1, vector<int>(n));
        table[0] = values;
        for (int level = 1; level < (int)table.size(); ++level) {
            int length = 1 << level;
            for (int i = 0; i + length <= n; ++i)
                table[level][i] =
                    min(table[level - 1][i], table[level - 1][i + length / 2]);
        }
    }

    // Minimum over non-empty half-open interval [left, right); O(1).
    int rangeMin(int left, int right) const {
        if (left < 0 || right <= left || right > (int)log2.size() - 1)
            throw out_of_range("range");
        int level = log2[right - left];
        return min(table[level][left], table[level][right - (1 << level)]);
    }
};
