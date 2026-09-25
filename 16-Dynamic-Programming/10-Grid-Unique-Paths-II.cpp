/*
Problem: Grid Unique Paths II
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP on Grids
Statement: Given a grid with obstacles (1), count down/right paths avoiding obstacles.
Sample Input: grid = [[0,0,0],[0,1,0],[0,0,0]]
Sample Output: 2
Explanation: Two routes pass around the centre obstacle.
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
    int uniquePathsWithObstacles(vector<vector<int>>& g) {
        int m = (int)g.size(), n = (int)g[0].size();
        vector<int> dp(n, 0);
        dp[0] = (g[0][0] == 0);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (g[i][j] == 1) {
                    dp[j] = 0;
                    continue;
                }
                if (i == 0 && j == 0) continue;
                int up = (i > 0) ? dp[j] : 0;
                int left = (j > 0) ? dp[j - 1] : 0;
                dp[j] = up + left;
            }
        }
        return dp[n - 1];
    }
};

int main() {
    vector<vector<int>> grid = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};

    Solution sol;
    auto ans = sol.uniquePathsWithObstacles(grid);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Obstacle cells contribute 0 paths.
Time Complexity:
O(m*n)
Space Complexity:
O(n)
Key Idea:
Rolling row;
zero out blocked cells.
*/
