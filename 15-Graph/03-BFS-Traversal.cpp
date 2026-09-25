/*
Problem: BFS Traversal
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Graph (BFS/DFS)
Statement: Given an undirected graph as an adjacency list and start node, return the BFS visit order.
Sample Input: n = 5, edges [(0,1),(0,2),(1,3),(2,4)], start = 0
Sample Output: [0, 1, 2, 3, 4]
Explanation: Neighbours are visited level by level.
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

vector<int> bfs(int n, vector<vector<int>>& g) {
    vector<int> vis(n, 0), o;
    queue<int> q;
    q.push(0);
    vis[0] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        o.push_back(u);
        for (int v : g[u]) if (!vis[v]) {
            vis[v] = 1;
            q.push(v);
        }
    }
    return o;
}

/*
Approach:
Queue layers.
Time Complexity:
O(V+E)
Space Complexity:
O(V)
Key Idea:
Visited on push.
*/
