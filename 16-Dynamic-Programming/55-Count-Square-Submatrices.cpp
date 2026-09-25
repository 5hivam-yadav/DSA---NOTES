/*
Problem: Count Square Submatrices
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Dynamic Programming
Statement: Given a binary matrix, count square submatrices of all 1s (DP cell = 1 + min of top/left/diagonal).
Sample Input: matrix = [[0,1,1,1],[1,1,1,1],[0,1,1,1]]
Sample Output: 15
Explanation: Squares of sizes 1, 2 and 3 total 15.
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
    int countSquares(vector<vector<int>>& m) {
        int R = m.size(), C = m[0].size(), ans = 0;
        vector<vector<int>> dp(R, vector<int>(C, 0));
        for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) {
            if (m[i][j] == 1) {
                dp[i][j] = 1;
                if (i > 0 && j > 0) dp[i][j] += min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
                ans += dp[i][j];
            }
        }
        return ans;
    }
};

int main() {
    vector<vector<int>> matrix = {{0, 1, 1, 1}, {1, 1, 1, 1}, {0, 1, 1, 1}};

    Solution sol;
    auto ans = sol.countSquares(matrix);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Min of 3 neighbors +1.
Time Complexity:
O(RC)
Space Complexity:
O(RC)
Key Idea:
Square ending here.
*/
