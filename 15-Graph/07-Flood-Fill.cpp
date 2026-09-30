/*
Problem: Flood Fill
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Graph (BFS/DFS)
Statement: Given an image, start pixel and new colour, recolour the 4-connected
region (DFS/BFS). Sample Input: image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc =
1, color = 2 Sample Output: [[2,2,2],[2,2,0],[2,0,1]] Explanation: Connected 1s
become 2s.
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
    void f(vector<vector<int>> &g, int r, int c, int old, int nw) {
        int R = g.size(), C = g[0].size();
        if (r < 0 || c < 0 || r >= R || c >= C || g[r][c] != old)
            return;
        g[r][c] = nw;
        f(g, r + 1, c, old, nw);
        f(g, r - 1, c, old, nw);
        f(g, r, c + 1, old, nw);
        f(g, r, c - 1, old, nw);
    }
    vector<vector<int>> floodFill(vector<vector<int>> &g, int r, int c,
                                  int nw) {
        if (g[r][c] != nw)
            f(g, r, c, g[r][c], nw);
        return g;
    }
};

/*
Approach:
Recolor connected.
Time Complexity:
O(RC)
Space Complexity:
O(RC)
Key Idea:
DFS repaint.
*/
