/*
Problem: Topo Sort BFS Kahn
Platform: GFG / Striver A2Z
Problem Number: -
Difficulty: Medium
Pattern: Topological Sort
Statement: Given a DAG, return a topological order with Kahn's algorithm (repeatedly emit indegree-0 nodes).
Sample Input: n = 4, edges = [[0,1],[0,2],[1,3],[2,3]]
Sample Output: [0,1,2,3] (any valid order)
Explanation: Indegree-zero nodes peel off layer by layer.
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

vector<int> kahn(int n, vector<vector<int>>& g) {
    vector<int> in(n, 0);
    for (int u = 0; u < n; u++) for (int v : g[u]) in[v]++;
    queue<int> q;
    for (int i = 0; i < n; i++) if (!in[i]) q.push(i);
    vector<int> o;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        o.push_back(u);
        for (int v : g[u]) if (--in[v] == 0) q.push(v);
    }
    return o;
}

int main() {
    int n = 4;
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 3}, {2, 3}};

    auto ans = kahn(n, edges);
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Indegree zero first.
Time Complexity:
O(V+E)
Space Complexity:
O(V)
Key Idea:
Cycle => short output.
*/
