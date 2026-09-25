/*
Problem: Zero One Matrix
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Graph (BFS/DFS)
Statement: Given a binary matrix, return distances to the nearest 0 for every cell (multi-source BFS).
Sample Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
Sample Output: [[0,0,0],[0,1,0],[0,0,0]]
Explanation: Only the centre is distance 1.
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
    vector<vector<int>> updateMatrix(vector<vector<int>>& m) {
        int R = m.size(), C = m[0].size();
        vector<vector<int>> d(R, vector<int>(C, INT_MAX));
        queue<pair<int, int>> q;
        for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) if (m[i][j] == 0) {
            d[i][j] = 0;
            q.push({i, j});
        }
        int dd[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (auto& k : dd) {
                int nx = x + k[0], ny = y + k[1];
                if (nx >= 0 && ny >= 0 && nx < R && ny < C && d[nx][ny] == INT_MAX) {
                    d[nx][ny] = d[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
        return d;
    }
};

int main() {
    vector<vector<int>> mat = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};

    Solution sol;
    auto ans = sol.updateMatrix(mat);
    for (int i = 0; i < (int)ans.size(); i++) {
        for (int j = 0; j < (int)ans[i].size(); j++) cout << ans[i][j] << " ";
        cout << endl;
    }
    return 0;
}

/*
Approach:
Multi-source from 0s.
Time Complexity:
O(RC)
Space Complexity:
O(RC)
Key Idea:
BFS distance layers.
*/
