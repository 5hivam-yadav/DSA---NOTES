/*
Problem: Eventual Safe States BFS
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Topological Sort
Statement: Given a directed graph, return nodes that never reach a cycle (reverse-graph Kahn from terminal nodes).
Sample Input: graph = [[1,2],[2,3],[5],[0],[5],[]]
Sample Output: [2,4,5]
Explanation: Nodes 2, 4, 5 end at terminals only.
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
    vector<int> eventualSafeNodes(vector<vector<int>>& g) {
        int n = g.size();
        vector<vector<int>> r(n);
        vector<int> out(n, 0);
        for (int u = 0; u < n; u++) for (int v : g[u]) {
            r[v].push_back(u);
            out[u]++;
        }
        queue<int> q;
        for (int i = 0; i < n; i++) if (!out[i]) q.push(i);
        vector<int> safe(n, 0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            safe[u] = 1;
            for (int p : r[u]) if (--out[p] == 0) q.push(p);
        }
        vector<int> o;
        for (int i = 0; i < n; i++) if (safe[i]) o.push_back(i);
        return o;
    }
};

int main() {
    vector<vector<int>> graph = {{1, 2}, {2, 3}, {5}, {0}, {5}, {}};

    Solution sol;
    auto ans = sol.eventualSafeNodes(graph);
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Reverse + terminal peel.
Time Complexity:
O(V+E)
Space Complexity:
O(V+E)
Key Idea:
Safe = leads to terminal.
*/
