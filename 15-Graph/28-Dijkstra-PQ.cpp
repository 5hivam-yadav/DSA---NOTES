/*
Problem: Dijkstra Priority Queue
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Shortest Path
Statement: Given a weighted graph with non-negative edges as an adjacency list with n nodes and source s, return shortest distances from s using Dijkstra with a min-heap.
Sample Input: n = 4, edges 0-1(4), 0-2(1), 2-1(2), 1-3(1), s = 0
Sample Output: [0, 3, 1, 4]
Explanation: Shortest paths are 0->2 (1), 0->2->1 (3), 0->2->1->3 (4).
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

vector<int> dijk(int n, vector<vector<pair<int, int>>>& g, int s) {
    const int INF = 1e9;
    vector<int> d(n, INF);
    d[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [c, u] = pq.top();
        pq.pop();
        if (c != d[u]) continue;
        for (auto [v, w] : g[u]) if (d[v] > c + w) {
            d[v] = c + w;
            pq.push({d[v], v});
        }
    }
    return d;
}

/*
Approach:
Relax min-first.
Time Complexity:
O(E log V)
Space Complexity:
O(V+E)
Key Idea:
Non-negative greedy.
*/
