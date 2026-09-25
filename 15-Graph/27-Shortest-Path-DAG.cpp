/*
Problem: Shortest Path DAG
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Shortest Path
Statement: Given a weighted DAG and source, return shortest distances via topological order + one relaxation pass.
Sample Input: n = 4, edges 0->1(2), 0->2(1), 2->3(4), s = 0
Sample Output: [0,2,1,5]
Explanation: Topo order relaxes each edge once.
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

vector<long long> shortDAG(int n, vector<vector<pair<int, int>>>& g, int s) {
    vector<int> in(n, 0);
    for (int u = 0; u < n; u++) for (auto& e : g[u]) in[e.first]++;
    queue<int> q;
    for (int i = 0; i < n; i++) if (!in[i]) q.push(i);
    vector<int> tp;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        tp.push_back(u);
        for (auto& e : g[u]) if (--in[e.first] == 0) q.push(e.first);
    }
    const long long INF = 4e18;
    vector<long long> d(n, INF);
    d[s] = 0;
    for (int u : tp) {
        if (d[u] == INF) continue;
        for (auto& e : g[u]) d[e.first] = min(d[e.first], d[u] + e.second);
    }
    return d;
}

/*
Approach:
Topo + relax.
Time Complexity:
O(V+E)
Space Complexity:
O(V+E)
Key Idea:
DAG order relax.
*/
