/*
Problem: Cherry Pickup II
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: DP on Grids
Statement: Given a grid, two robots start top-left/top-right moving down (-1/0/+1) sharing cells; maximize cherries collected.
Sample Input: grid = [[3,1,1],[2,5,1],[1,5,5]]
Sample Output: 24
Explanation: Optimal joint walk gathers 24.
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
    int cherryPickup(vector<vector<int>>& g) {
        int m = (int)g.size(), n = (int)g[0].size();
        vector<vector<int>> prev(n, vector<int>(n, -1e9)), cur(n, vector<int>(n, -1e9));
        for (int c1 = 0; c1 < n; c1++)
        for (int c2 = 0; c2 < n; c2++)
        prev[c1][c2] = (c1 == c2) ? g[m - 1][c1] : g[m - 1][c1] + g[m - 1][c2];
        for (int r = m - 2; r >= 0; r--) {
            for (int c1 = 0; c1 < n; c1++) {
                for (int c2 = 0; c2 < n; c2++) {
                    int best = -1e9;
                    for (int d1 = -1; d1 <= 1; d1++) {
                        for (int d2 = -1; d2 <= 1; d2++) {
                            int nc1 = c1 + d1, nc2 = c2 + d2;
                            if (nc1 < 0 || nc1 >= n || nc2 < 0 || nc2 >= n) continue;
                            best = max(best, prev[nc1][nc2]);
                        }
                    }
                    int add = (c1 == c2) ? g[r][c1] : g[r][c1] + g[r][c2];
                    cur[c1][c2] = add + best;
                }
            }
            prev.swap(cur);
        }
        return prev[0][n - 1];
    }
};

int main() {
    vector<vector<int>> grid = {{3, 1, 1}, {2, 5, 1}, {1, 5, 5}};

    Solution sol;
    auto ans = sol.cherryPickup(grid);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Two robots move together, 3x3 = 9 transitions.
Time Complexity:
O(m*n*n*9)
Space Complexity:
O(n*n)
Key Idea:
Shared cell counted once.
*/
