/*
Problem: Cycle Undirected BFS
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Graph (BFS/DFS)
Statement: Given an undirected graph, return true if a cycle exists using BFS
with parent tracking. Sample Input: n = 3, edges = [[0,1],[1,2],[2,0]] Sample
Output: true Explanation: Triangle edges form a cycle.
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

bool cycBFS(int n, vector<vector<int>> &g) {
    vector<int> v(n, 0);
    for (int s = 0; s < n; s++) {
        if (v[s])
            continue;
        queue<pair<int, int>> q;
        q.push({s, -1});
        v[s] = 1;
        while (!q.empty()) {
            auto [u, p] = q.front();
            q.pop();
            for (int x : g[u]) {
                if (!v[x]) {
                    v[x] = 1;
                    q.push({x, u});
                } else if (x != p)
                    return true;
            }
        }
    }
    return false;
}

int main() {
    int n = 3;
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 0}};

    auto ans = cycBFS(n, edges);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
Visited non-parent.
Time Complexity:
O(V+E)
Space Complexity:
O(V)
Key Idea:
Parent check.
*/
