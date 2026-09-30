/*
Problem: Cycle Undirected DFS
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Graph (BFS/DFS)
Statement: Given an undirected graph, return true if a cycle exists using DFS
with parent tracking. Sample Input: n = 3, edges = [[0,1],[1,2],[2,0]] Sample
Output: true Explanation: Back edge to the parent-free ancestor found.
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

bool f(int u, int p, vector<vector<int>> &g, vector<int> &v) {
    v[u] = 1;
    for (int x : g[u]) {
        if (!v[x]) {
            if (f(x, u, g, v))
                return true;
        } else if (x != p)
            return true;
    }
    return false;
}

/*
Approach:
Same parent rule.
Time Complexity:
O(V+E)
Space Complexity:
O(V)
Key Idea:
DFS variant.
*/
