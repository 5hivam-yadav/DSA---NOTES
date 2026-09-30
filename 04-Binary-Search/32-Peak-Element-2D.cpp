/*
Problem: Peak Element 2D
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search
Statement: Given a matrix, return any peak (value >= its four neighbours) in O(m
log n or n log m). Sample Input: mat = [[1,4],[3,2]] Sample Output: [0, 1]
(value 4) Explanation: 4 beats its neighbours 1 and 2.
*/
#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
  public:
    vector<int> findPeakGrid(vector<vector<int>> &m) {
        int R = m.size(), C = m[0].size(), lo = 0, hi = C - 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2, r = 0;
            for (int i = 0; i < R; i++)
                if (m[i][mid] > m[r][mid])
                    r = i;
            int l = (mid > 0 ? m[r][mid - 1] : -1),
                rr = (mid + 1 < C ? m[r][mid + 1] : -1);
            if (m[r][mid] > l && m[r][mid] > rr)
                return {r, mid};
            else if (m[r][mid] < rr)
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        return {-1, -1};
    }
};

int main() {
    vector<vector<int>> mat = {{1, 4}, {3, 2}};

    Solution sol;
    auto ans = sol.findPeakGrid(mat);
    for (int i = 0; i < (int)ans.size(); i++)
        cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Max-col + side compare.
Time Complexity:
O(R log C)
Space Complexity:
O(1)
Key Idea:
Column BS on row-max.
*/
