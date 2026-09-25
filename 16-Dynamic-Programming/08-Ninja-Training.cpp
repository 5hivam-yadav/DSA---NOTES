/*
Problem: Ninja Training
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP - 1D
Statement: Given points[day][activity], maximize total over days never repeating an activity on consecutive days.
Sample Input: points = [[1,2,5],[3,1,1]]
Sample Output: 8
Explanation: Day 0 activity 2 (5) + day 1 activity 0 (3) = 8.
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

int ninja(vector<vector<int>>& p) {
    int n = p.size();
    vector<int> dp(4, 0);
    for (int t = 0; t < 3; t++) dp[t] = p[0][t];
    for (int d = 1; d < n; d++) {
        vector<int> nd(4, 0);
        for (int last = 0; last < 4; last++) {
            int b = 0;
            for (int t = 0; t < 3; t++) if (t != last) b = max(b, p[d][t] + dp[t]);
            nd[last] = b;
        }
        dp = nd;
    }
    return dp[3];
}

int main() {
    vector<vector<int>> points = {{1, 2, 5}, {3, 1, 1}};

    auto ans = ninja(points);
    cout << ans << endl;
    return 0;
}

/*
Approach:
No repeat task.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Last-task state.
*/
