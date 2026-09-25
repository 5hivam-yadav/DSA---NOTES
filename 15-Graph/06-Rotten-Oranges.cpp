/*
Problem: Rotten Oranges
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Graph (BFS/DFS)
Statement: Given a grid of fresh (1), rotten (2) and empty (0) cells, return minutes until all fresh rot, or -1 if impossible (multi-source BFS).
Sample Input: grid = [[2, 1, 1], [1, 1, 0], [0, 1, 1]]
Sample Output: 4
Explanation: Rot spreads level by level, finishing in 4 minutes.
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
    int orangesRotting(vector<vector<int>>& g) {
        int R = g.size(), C = g[0].size();
        queue<pair<int, int>> q;
        int fresh = 0;
        for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) {
            if (g[i][j] == 2) q.push({i, j});
            if (g[i][j] == 1) fresh++;
        }
        int t = 0, d[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while (!q.empty() && fresh > 0) {
            int n = q.size();
            while (n--) {
                auto [x, y] = q.front();
                q.pop();
                for (auto& dd : d) {
                    int nx = x + dd[0], ny = y + dd[1];
                    if (nx >= 0 && ny >= 0 && nx < R && ny < C && g[nx][ny] == 1) {
                        g[nx][ny] = 2;
                        fresh--;
                        q.push({nx, ny});
                    }
                }
            }
            t++;
        }
        return fresh == 0 ? t : -1;
    }
};

int main() {
    vector<vector<int>> grid = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};

    Solution sol;
    auto ans = sol.orangesRotting(grid);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Level = minute.
Time Complexity:
O(RC)
Space Complexity:
O(RC)
Key Idea:
Multi-source BFS.
*/
