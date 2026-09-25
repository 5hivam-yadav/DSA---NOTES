/*
Problem: Minimum Path Sum
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given a cost grid, return the minimum path sum from top-left to bottom-right moving down/right.
Sample Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
Sample Output: 7
Explanation: Path 1->3->1->1->1 sums to 7.
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
    int minPathSum(vector<vector<int>>& g) {
        int m = (int)g.size(), n = (int)g[0].size();
        vector<int> dp(n, 0);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) dp[j] = g[i][j];
                else if (i == 0) dp[j] = dp[j - 1] + g[i][j];
                else if (j == 0) dp[j] = dp[j] + g[i][j];
                else dp[j] = min(dp[j], dp[j - 1]) + g[i][j];
            }
        }
        return dp[n - 1];
    }
};

int main() {
    vector<vector<int>> grid = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};

    Solution sol;
    auto ans = sol.minPathSum(grid);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Move only down/right, take min of top/left.
Time Complexity:
O(m*n)
Space Complexity:
O(n)
Key Idea:
In-place rolling minimum cost.
*/
