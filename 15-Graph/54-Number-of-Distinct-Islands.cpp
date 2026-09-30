/*
Problem: Number of Distinct Islands
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Graph (BFS/DFS)
Statement: Given a grid, count distinct island shapes (normalize each island by
relative coordinates in a set). Sample Input: grid with two L-shapes and one
square Sample Output: 2 Explanation: The two L shapes match; the square differs.
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

void f4(vector<vector<int>> &g, int r, int c, vector<pair<int, int>> &sh,
        int br, int bc) {
    int R = g.size(), C = g[0].size();
    if (r < 0 || c < 0 || r >= R || c >= C || g[r][c] != 1)
        return;
    g[r][c] = 0;
    sh.push_back({r - br, c - bc});
    f4(g, r + 1, c, sh, br, bc);
    f4(g, r - 1, c, sh, br, bc);
    f4(g, r, c + 1, sh, br, bc);
    f4(g, r, c - 1, sh, br, bc);
}

/*
Approach:
Relative shape set.
Time Complexity:
O(RC log)
Space Complexity:
O(RC)
Key Idea:
Translate-invariant.
*/
