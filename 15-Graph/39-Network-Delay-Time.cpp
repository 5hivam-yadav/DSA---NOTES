/*
Problem: Network Delay Time
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Shortest Path
Statement: Given directed times, source k and n nodes, return the time for all nodes to receive the signal (max of Dijkstra distances, -1 if unreachable).
Sample Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
Sample Output: 2
Explanation: Distances are [1,0,1,2]; max is 2.
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
    int networkDelayTime(vector<vector<int>>& t, int n, int k) {
        vector<vector<pair<int, int>>> g(n + 1);
        for (auto& e : t) g[e[0]].push_back({e[1], e[2]});
        const int INF = 1e9;
        vector<int> d(n + 1, INF);
        d[k] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, k});
        while (!pq.empty()) {
            auto [c, u] = pq.top();
            pq.pop();
            if (c != d[u]) continue;
            for (auto [v, w] : g[u]) if (d[v] > c + w) {
                d[v] = c + w;
                pq.push({d[v], v});
            }
        }
        int b = 0;
        for (int i = 1; i <= n; i++) {
            if (d[i] == INF) return -1;
            b = max(b, d[i]);
        }
        return b;
    }
};

int main() {
    vector<vector<int>> times = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    int n = 4;
    int k = 2;

    Solution sol;
    auto ans = sol.networkDelayTime(times, n, k);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Max of Dijkstra.
Time Complexity:
O(E log V)
Space Complexity:
O(V+E)
Key Idea:
Broadcast max.
*/
