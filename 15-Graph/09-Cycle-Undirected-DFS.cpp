/*
Problem: Cycle Undirected DFS
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Graph (BFS/DFS)
Statement: Given an undirected graph, return true if a cycle exists using DFS with parent tracking.
Sample Input: n = 3, edges = [[0,1],[1,2],[2,0]]
Sample Output: true
Explanation: Back edge to the parent-free ancestor found.
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

bool f(int u, int p, vector<vector<int>>& g, vector<int>& v) {
    v[u] = 1;
    for (int x : g[u]) {
        if (!v[x]) {
            if (f(x, u, g, v)) return true;
        }
        else if (x != p) return true;
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
