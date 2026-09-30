/*
Problem: Prims Minimum Spanning Tree
Platform: GFG / LeetCode
Problem Number: -
Difficulty: Medium
Pattern: MST
Statement: Given an adjacency list and start, return the MST weight growing the
cheapest frontier edge with a min-heap. Sample Input: n = 4, sample weighted
graph Sample Output: minimum total weight Explanation: Cut property picks the
cheapest crossing edge each step.
*/
#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

int prims(int n, vector<vector<pair<int, int>>> &g) {
    vector<int> vis(n, 0);
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;
    pq.push({0, 0});
    int c = 0;
    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = 1;
        c += w;
        for (auto [v, ww] : g[u])
            if (!vis[v])
                pq.push({ww, v});
    }
    return c;
}

/*
Approach:
Grow min fringe.
Time Complexity:
O(E log V)
Space Complexity:
O(V+E)
Key Idea:
Cut property.
*/
