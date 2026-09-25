/*
Problem: DFS Traversal
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Graph (BFS/DFS)
Statement: Given an undirected graph as an adjacency list and start node, return a DFS visit order.
Sample Input: n = 5, edges [(0,1),(0,2),(1,3),(2,4)], start = 0
Sample Output: [0, 1, 3, 2, 4]
Explanation: Each branch is explored depth-first.
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

void dfs(int u, vector<vector<int>>& g, vector<int>& vis, vector<int>& o) {
    vis[u] = 1;
    o.push_back(u);
    for (int v : g[u]) if (!vis[v]) dfs(v, g, vis, o);
}

/*
Approach:
Recur neighbors.
Time Complexity:
O(V+E)
Space Complexity:
O(V)
Key Idea:
Mark on entry.
*/
