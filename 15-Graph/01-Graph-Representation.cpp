/*
Problem: Graph Representation
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Graph (BFS/DFS)
Statement: Given n and an edge list, build the adjacency list of an undirected graph.
Sample Input: n = 3, edges = [[0,1],[1,2]]
Sample Output: [[1],[0,2],[1]]
Explanation: Each edge appears in both endpoint lists.
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

vector<vector<int>> adjList(int n, vector<pair<int, int>>& e) {
    vector<vector<int>> g(n);
    for (auto& p : e) {
        g[p.first].push_back(p.second);
        g[p.second].push_back(p.first);
    }
    return g;
}
vector<vector<int>> adjMatrix(int n, vector<pair<int, int>>& e) {
    vector<vector<int>> m(n, vector<int>(n, 0));
    for (auto& p : e) {
        m[p.first][p.second] = 1;
        m[p.second][p.first] = 1;
    }
    return m;
}

/*
Approach:
List vs matrix.
Time Complexity:
O(V+E)
Space Complexity:
O(V+E)
Key Idea:
List default sparse.
*/
