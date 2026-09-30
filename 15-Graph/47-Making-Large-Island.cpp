/*
Problem: Making Large Island
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: DSU
Statement: Given a binary grid, return the largest island possible by flipping
at most one 0 to 1 (label islands + try each 0). Sample Input: grid =
[[1,0],[0,1]] Sample Output: 3 Explanation: Flipping either 0 joins both 1s into
size 3.
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
    int R, C;
    int dfs(vector<vector<int>> &g, int r, int c, int id) {
        if (r < 0 || c < 0 || r >= R || c >= C || g[r][c] != 1)
            return 0;
        g[r][c] = id;
        return 1 + dfs(g, r + 1, c, id) + dfs(g, r - 1, c, id) +
               dfs(g, r, c + 1, id) + dfs(g, r, c - 1, id);
    }
    int largestIsland(vector<vector<int>> &g) {
        R = g.size();
        C = g[0].size();
        unordered_map<int, int> sz;
        int id = 2, b = 0;
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                if (g[i][j] == 1) {
                    int s = dfs(g, i, j, id);
                    sz[id++] = s;
                    b = max(b, s);
                }
        return b;
    }
};
// Flip best 0: neighbor id set + 1.

/*
Approach:
Label islands.
Time Complexity:
O(RC)
Space Complexity:
O(RC)
Key Idea:
Island ids.
*/
