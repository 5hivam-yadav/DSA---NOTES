/*
Problem: Surrounded Regions
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Graph (BFS/DFS)
Statement: Given a board of X/O, flip surrounded O regions to X (keep border-connected O via DFS from borders).
Sample Input: board = [["X","X","X"],["X","O","X"],["X","X","X"]]
Sample Output: [["X","X","X"],["X","X","X"],["X","X","X"]]
Explanation: The lone O is fully surrounded.
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
    void f(vector<vector<char>>& b, int r, int c) {
        int R = b.size(), C = b[0].size();
        if (r < 0 || c < 0 || r >= R || c >= C || b[r][c] != 'O') return;
        b[r][c] = 'S';
        f(b, r+1, c);
        f(b, r-1, c);
        f(b, r, c+1);
        f(b, r, c-1);
    }
    void solve(vector<vector<char>>& b) {
        if (b.empty()) return;
        int R = b.size(), C = b[0].size();
        for (int i = 0; i < R; i++) {
            f(b, i, 0);
            f(b, i, C-1);
        }
        for (int j = 0; j < C; j++) {
            f(b, 0, j);
            f(b, R-1, j);
        }
        for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) {
            if (b[i][j] == 'O') b[i][j] = 'X';
            else if (b[i][j] == 'S') b[i][j] = 'O';
        }
    }
};

/*
Approach:
Keep border-connected.
Time Complexity:
O(RC)
Space Complexity:
O(RC)
Key Idea:
Border DFS first.
*/
