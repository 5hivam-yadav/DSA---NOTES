/*
Problem: Min Edges Reverse
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Shortest Path
Statement: Given a directed graph, return the minimum edge reversals so 0 reaches all nodes (0-1 BFS: original 0, reverse 1).
Sample Input: n = 4, edges = [[0,1],[1,2],[2,0],[2,3]]
Sample Output: 0
Explanation: Node 0 already reaches everyone.
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

int minRev(int n, vector<pair<int, int>>& e, int s, int t) {
    vector<vector<pair<int, int>>> g(n);
    for (auto& p : e) {
        g[p.first].push_back({p.second, 0});
        g[p.second].push_back({p.first, 1});
    }
    const int INF = 1e9;
    vector<int> d(n, INF);
    d[s] = 0;
    deque<int> dq;
    dq.push_front(s);
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        for (auto [v, w] : g[u]) if (d[v] > d[u] + w) {
            d[v] = d[u] + w;
            if (w == 0) dq.push_front(v);
            else dq.push_back(v);
        }
    }
    return d[t] == INF ? -1 : d[t];
}

/*
Approach:
Reverse = cost 1.
Time Complexity:
O(V+E)
Space Complexity:
O(V+E)
Key Idea:
0-1 BFS.
*/
