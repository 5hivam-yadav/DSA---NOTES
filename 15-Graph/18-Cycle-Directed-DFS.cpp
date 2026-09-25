/*
Problem: Cycle Directed DFS
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Graph (BFS/DFS)
Statement: Given a directed graph, return true if a cycle exists using DFS colours (white/gray/black or recursion stack).
Sample Input: n = 2, edges = [[0,1],[1,0]]
Sample Output: true
Explanation: 0 -> 1 -> 0 closes a directed cycle.
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

bool f(int u, vector<vector<int>>& g, vector<int>& v, vector<int>& s) {
    v[u] = s[u] = 1;
    for (int x : g[u]) {
        if (!v[x]) {
            if (f(x, g, v, s)) return true;
        }
        else if (s[x]) return true;
    }
    s[u] = 0;
    return false;
}

/*
Approach:
RecStack back edge.
Time Complexity:
O(V+E)
Space Complexity:
O(V)
Key Idea:
Stack membership.
*/
