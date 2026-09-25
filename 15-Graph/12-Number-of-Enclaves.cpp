/*
Problem: Number of Enclaves
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Graph (BFS/DFS)
Statement: Given a grid of 0/1, count land cells unreachable from the boundary (flood boundary land first).
Sample Input: grid = [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
Sample Output: 3
Explanation: Three inner 1s never touch the border.
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
    void f(vector<vector<int>>& g, int r, int c) {
        int R = g.size(), C = g[0].size();
        if (r < 0 || c < 0 || r >= R || c >= C || g[r][c] != 1) return;
        g[r][c] = 0;
        f(g, r+1, c);
        f(g, r-1, c);
        f(g, r, c+1);
        f(g, r, c-1);
    }
    int numEnclaves(vector<vector<int>>& g) {
        int R = g.size(), C = g[0].size();
        for (int i = 0; i < R; i++) {
            f(g, i, 0);
            f(g, i, C-1);
        }
        for (int j = 0; j < C; j++) {
            f(g, 0, j);
            f(g, R-1, j);
        }
        int c = 0;
        for (auto& r : g) for (int x : r) c += x;
        return c;
    }
};

/*
Approach:
Remove border land.
Time Complexity:
O(RC)
Space Complexity:
O(RC)
Key Idea:
Same border trick.
*/
