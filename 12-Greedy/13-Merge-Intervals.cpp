/*
Problem: Merge Intervals
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Greedy
Statement: Given intervals, merge all overlapping ones after sorting by start.
Sample Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Sample Output: [[1,6],[8,10],[15,18]]
Explanation: [1,3] and [2,6] merge into [1,6].
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <stack>
#include <functional>
#include <numeric>
#include <cmath>
#include <climits>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& v) {
        sort(v.begin(), v.end());
        vector<vector<int>> r;
        for (auto& p : v) {
            if (r.empty() || p[0] > r.back()[1]) r.push_back(p);
            else r.back()[1] = max(r.back()[1], p[1]);
        }
        return r;
    }
};

int main() {
    vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};

    Solution sol;
    auto ans = sol.merge(intervals);
    for (int i = 0; i < (int)ans.size(); i++) {
        for (int j = 0; j < (int)ans[i].size(); j++) cout << ans[i][j] << " ";
        cout << endl;
    }
    return 0;
}

/*
Approach:
Sort + absorb.
Time Complexity:
O(n log n)
Space Complexity:
O(n)
Key Idea:
Overlap extends end.
*/
