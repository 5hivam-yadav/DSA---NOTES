/*
Problem: Non Overlapping Intervals
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Greedy
Statement: Given intervals, return the minimum removals to make the rest non-overlapping (sort by end, count overlaps).
Sample Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
Sample Output: 1
Explanation: Removing [1,3] leaves the rest disjoint.
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
    int eraseOverlapIntervals(vector<vector<int>>& v) {
        sort(v.begin(), v.end(), [](auto& a, auto& b) { return a[1] < b[1]; });
        int c = 0, last = INT_MIN;
        for (auto& p : v) {
            if (p[0] >= last) last = p[1];
            else c++;
        }
        return c;
    }
};

int main() {
    vector<vector<int>> intervals = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};

    Solution sol;
    auto ans = sol.eraseOverlapIntervals(intervals);
    cout << ans << endl;
    return 0;
}

/*
Approach:
End-sort keep max.
Time Complexity:
O(n log n)
Space Complexity:
O(1)
Key Idea:
Meetings variant.
*/
