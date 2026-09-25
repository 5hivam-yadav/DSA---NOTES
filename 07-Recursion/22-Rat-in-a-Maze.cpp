/*
Problem: Rat in a Maze
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Backtracking
Statement: Given an n x n maze of 0/1 cells, return all paths from (0,0) to (n-1,n-1) moving D/L/R/U through 1s.
Sample Input: maze = [[1,0],[1,1]]
Sample Output: ["DR"]
Explanation: Down then right reaches the goal.
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

void f(vector<vector<int>>& m, int r, int c, string path, vector<string>& ans, vector<vector<int>>& vis) {
    int n = m.size();
    if (r == n - 1 && c == n - 1) {
        ans.push_back(path);
        return;
    }
    vis[r][c] = 1;
    int dr[4] = {1, 0, 0, -1}, dc[4] = {0, -1, 1, 0};
    char ch[4] = {'D', 'L', 'R', 'U'};
    for (int k = 0; k < 4; k++) {
        int nr = r + dr[k], nc = c + dc[k];
        if (nr >= 0 && nc >= 0 && nr < n && nc < n && !vis[nr][nc] && m[nr][nc] == 1) f(m, nr, nc, path + ch[k], ans, vis);
    }
    vis[r][c] = 0;
}
  // Lexicographic D L R U order.

int main() {
    vector<vector<int>> maze = {{1, 0}, {1, 1}};
    int n = maze.size();
    vector<vector<int>> vis(n, vector<int>(n, 0));
    vector<string> ans;
    f(maze, 0, 0, "", ans, vis);
    for (size_t i = 0; i < ans.size(); i++) cout << ans[i] << (i + 1 < ans.size() ? " " : "");
    cout << endl;
    return 0;
}

/*
Approach:
DFS 4-dir + unmark.
Time Complexity:
O(4^(n^2))
Space Complexity:
O(n^2)
Key Idea:
Mark/unmark path.
*/
