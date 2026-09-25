/*
Problem: Insert Interval
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Greedy
Statement: Given sorted non-overlapping intervals and a new interval, insert and merge in one pass.
Sample Input: intervals = [[1,3],[6,9]], new = [2,5]
Sample Output: [[1,5],[6,9]]
Explanation: [2,5] overlaps [1,3] into [1,5].
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
    vector<vector<int>> insert(vector<vector<int>>& v, vector<int>& nw) {
        vector<vector<int>> r;
        int i = 0, n = v.size();
        while (i < n && v[i][1] < nw[0]) r.push_back(v[i++]);
        while (i < n && v[i][0] <= nw[1]) {
            nw[0] = min(nw[0], v[i][0]);
            nw[1] = max(nw[1], v[i][1]);
            i++;
        }
        r.push_back(nw);
        while (i < n) r.push_back(v[i++]);
        return r;
    }
};

int main() {
    vector<vector<int>> intervals = {{1, 3}, {6, 9}};
    vector<int> newInterval = {2, 5};

    Solution sol;
    auto ans = sol.insert(intervals, newInterval);
    for (int i = 0; i < (int)ans.size(); i++) {
        for (int j = 0; j < (int)ans[i].size(); j++) cout << ans[i][j] << " ";
        cout << endl;
    }
    return 0;
}

/*
Approach:
Before/overlap/after.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Merge middle run.
*/
