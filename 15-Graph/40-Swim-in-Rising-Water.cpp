/*
Problem: Swim in Rising Water
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Shortest Path
Statement: Given an n x n grid of heights, return the minimum time to swim from (0,0) to (n-1,n-1) where time = max height on path (Dijkstra on max-edge).
Sample Input: grid = [[0,2],[1,3]]
Sample Output: 3
Explanation: Path 0->1->3 peaks at 3, the minimum possible.
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
    int swimInWater(vector<vector<int>>& g) {
        int n = g.size();
        vector<vector<int>> d(n, vector<int>(n, INT_MAX));
        d[0][0] = g[0][0];
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
        pq.push({g[0][0], 0, 0});
        int dd[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while (!pq.empty()) {
            auto [c, x, y] = pq.top();
            pq.pop();
            if (c != d[x][y]) continue;
            if (x == n - 1 && y == n - 1) return c;
            for (auto& k : dd) {
                int nx = x + k[0], ny = y + k[1];
                if (nx >= 0 && ny >= 0 && nx < n && ny < n) {
                    int nc = max(c, g[nx][ny]);
                    if (nc < d[nx][ny]) {
                        d[nx][ny] = nc;
                        pq.push({nc, nx, ny});
                    }
                }
            }
        }
        return 0;
    }
};

int main() {
    vector<vector<int>> grid = {{0, 2}, {1, 3}};

    Solution sol;
    auto ans = sol.swimInWater(grid);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Minimax like effort.
Time Complexity:
O(n^2 log n)
Space Complexity:
O(n^2)
Key Idea:
Water level max.
*/
