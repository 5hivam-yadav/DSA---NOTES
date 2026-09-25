/*
Problem: Zero One BFS
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Graph (BFS/DFS)
Statement: Given a graph with 0/1 edge weights and source, return shortest distances with 0-1 BFS (deque).
Sample Input: n = 4, edges 0-1(0), 1-2(1), 0-2(1), s = 0
Sample Output: [0,0,1]
Explanation: 0->1 costs 0, then 1->2 costs 1.
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

vector<int> zeroOne(int n, vector<vector<pair<int, int>>>& g, int s) {
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
    return d;
}

/*
Approach:
Deque 0-front 1-back.
Time Complexity:
O(V+E)
Space Complexity:
O(V+E)
Key Idea:
Weights 0/1 only.
*/
