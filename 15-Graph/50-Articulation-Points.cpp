/*
Problem: Articulation Points
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Graph (BFS/DFS)
Statement: Given an undirected graph, return its articulation points (removal increases components) via DFS discovery/low times.
Sample Input: n = 5, edges = [[0,1],[1,2],[2,0],[1,3],[3,4]]
Sample Output: [1, 3]
Explanation: Removing 1 or 3 disconnects the graph.
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

void f2(int u, int p, vector<vector<int>>& g, vector<int>& d, vector<int>& lo, vector<int>& ap, int& t) {
    d[u] = lo[u] = t++;
    int ch = 0;
    for (int v : g[u]) {
        if (v == p) continue;
        if (d[v] == -1) {
            ch++;
            f2(v, u, g, d, lo, ap, t);
            lo[u] = min(lo[u], lo[v]);
            if (p != -1 && lo[v] >= d[u]) ap[u] = 1;
        }
        else lo[u] = min(lo[u], d[v]);
    }
    if (p == -1 && ch > 1) ap[u] = 1;
}

/*
Approach:
Root 2+ kids else low>=disc.
Time Complexity:
O(V+E)
Space Complexity:
O(V)
Key Idea:
Cut vertices.
*/
