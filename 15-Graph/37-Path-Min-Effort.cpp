/*
Problem: Path Min Effort
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Shortest Path
Statement: Given heights grid, return the minimum effort path from corner to corner where effort = max adjacent jump (Dijkstra on max-edge).
Sample Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
Sample Output: 2
Explanation: Route 1->3->5->3->5 peaks at jump 2.
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
    int minimumEffortPath(vector<vector<int>>& h) {
        int R = h.size(), C = h[0].size();
        vector<vector<int>> d(R, vector<int>(C, INT_MAX));
        d[0][0] = 0;
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
        pq.push({0, 0, 0});
        int dd[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while (!pq.empty()) {
            auto [c, x, y] = pq.top();
            pq.pop();
            if (c != d[x][y]) continue;
            if (x == R - 1 && y == C - 1) return c;
            for (auto& k : dd) {
                int nx = x + k[0], ny = y + k[1];
                if (nx >= 0 && ny >= 0 && nx < R && ny < C) {
                    int nc = max(c, abs(h[nx][ny] - h[x][y]));
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
    vector<vector<int>> heights = {{1, 2, 2}, {3, 8, 2}, {5, 3, 5}};

    Solution sol;
    auto ans = sol.minimumEffortPath(heights);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Minimax Dijkstra.
Time Complexity:
O(RC log RC)
Space Complexity:
O(RC)
Key Idea:
Max-edge cost.
*/
