/*
Problem: Merge Overlapping Intervals
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Arrays
Statement: Given intervals, merge all overlapping ones after sorting by start.
Sample Input: intervals = [[1, 3], [2, 6], [8, 10], [15, 18]]
Sample Output: [[1, 6], [8, 10], [15, 18]]
Explanation: [1, 3] and [2, 6] merge into [1, 6].
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
    vector<vector<int>> merge(vector<vector<int>> &v) {
        sort(v.begin(), v.end());
        vector<vector<int>> r;
        for (auto &p : v) {
            if (r.empty() || p[0] > r.back()[1])
                r.push_back(p);
            else
                r.back()[1] = max(r.back()[1], p[1]);
        }
        return r;
    }
};

int main() {
    vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};

    Solution sol;
    auto ans = sol.merge(intervals);
    for (int i = 0; i < (int)ans.size(); i++) {
        for (int j = 0; j < (int)ans[i].size(); j++)
            cout << ans[i][j] << " ";
        cout << endl;
    }
    return 0;
}

/*
Approach:
Sort by start, absorb.
Time Complexity:
O(n log n)
Space Complexity:
O(n)
Key Idea:
Overlap extends end.
*/
