/*
Problem: Connect All Points Min Cost
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: MST
Statement: Given points on a plane, return the minimum total cost to connect all of them where cost(i, j) = Manhattan distance (MST via Prim on a dense graph).
Sample Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
Sample Output: 20
Explanation: Edges 0-1 (4), 1-3 (3), 3-4 (4) and 1-2 (9) form the MST, totalling 20.
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
    int minCostConnectPoints(vector<vector<int>>& p) {
        int n = p.size();
        vector<int> vis(n, 0);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 0});
        int c = 0, used = 0;
        while (used < n) {
            auto [w, u] = pq.top();
            pq.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            c += w;
            used++;
            for (int v = 0; v < n; v++) if (!vis[v]) pq.push({abs(p[u][0]-p[v][0]) + abs(p[u][1]-p[v][1]), v});
        }
        return c;
    }
};

int main() {
    vector<vector<int>> points = {{0, 0}, {2, 2}, {3, 10}, {5, 2}, {7, 0}};

    Solution sol;
    auto ans = sol.minCostConnectPoints(points);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Prim on complete graph.
Time Complexity:
O(n^2 log n)
Space Complexity:
O(n^2)
Key Idea:
Manhattan MST.
*/
