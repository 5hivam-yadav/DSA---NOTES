/*
Problem: Shortest Path Binary Maze
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Shortest Path
Statement: Given a binary grid, start and destination, return the shortest path length through 1s (BFS).
Sample Input: grid = [[1,1,1],[1,0,1],[1,1,1]], src = (0,0), dst = (2,2)
Sample Output: 4
Explanation: Four steps route around the centre wall.
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

int shortMaze(vector<vector<int>>& g, pair<int, int> s, pair<int, int> t) {
    int R = g.size(), C = g[0].size();
    vector<vector<int>> d(R, vector<int>(C, INT_MAX));
    queue<pair<int, int>> q;
    q.push(s);
    d[s.first][s.second] = 0;
    int dd[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        if (x == t.first && y == t.second) return d[x][y];
        for (auto& k : dd) {
            int nx = x + k[0], ny = y + k[1];
            if (nx >= 0 && ny >= 0 && nx < R && ny < C && g[nx][ny] == 1 && d[nx][ny] == INT_MAX) {
                d[nx][ny] = d[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
    return -1;
}

/*
Approach:
BFS on open cells.
Time Complexity:
O(RC)
Space Complexity:
O(RC)
Key Idea:
Unit grid BFS.
*/
