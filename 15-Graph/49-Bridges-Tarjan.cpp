/*
Problem: Bridges Tarjan
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Graph (BFS/DFS)
Statement: Given an undirected graph, return its bridges (edges whose removal increases components) with DFS low-link.
Sample Input: n = 4, edges = [[0,1],[1,2],[2,0],[1,3]]
Sample Output: [[1,3]]
Explanation: Only 1-3 is a bridge; the triangle has none.
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
    vector<vector<int>> ans;
    vector<int> d, lo;
    int t = 0;
    void f(int u, int p, vector<vector<int>>& g) {
        d[u] = lo[u] = t++;
        for (int v : g[u]) {
            if (v == p) continue;
            if (d[v] == -1) {
                f(v, u, g);
                lo[u] = min(lo[u], lo[v]);
                if (lo[v] > d[u]) ans.push_back({u, v});
            }
            else lo[u] = min(lo[u], d[v]);
        }
    }
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& e) {
        vector<vector<int>> g(n);
        for (auto& x : e) {
            g[x[0]].push_back(x[1]);
            g[x[1]].push_back(x[0]);
        }
        d.assign(n, -1);
        lo.assign(n, 0);
        f(0, -1, g);
        return ans;
    }
};

/*
Approach:
low > disc = bridge.
Time Complexity:
O(V+E)
Space Complexity:
O(V)
Key Idea:
DFS lowlink.
*/
