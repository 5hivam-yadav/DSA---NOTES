/*
Problem: Eventual Safe States DFS
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Topological Sort
Statement: Given a directed graph, return nodes that never reach a cycle using DFS colours (nodes on no back edge are safe).
Sample Input: graph = [[1,2],[2,3],[5],[0],[5],[]]
Sample Output: [2,4,5]
Explanation: Only 2, 4, 5 avoid cycles.
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
    bool f(vector<vector<int>>& g, vector<int>& st, int u) {
        st[u] = 1;
        for (int v : g[u]) {
            if (st[v] == 1) return false;
            if (st[v] == 0 && !f(g, st, v)) return false;
        }
        st[u] = 2;
        return true;
    }
    vector<int> eventualSafeNodes(vector<vector<int>>& g) {
        int n = g.size();
        vector<int> st(n, 0);
        vector<int> o;
        for (int i = 0; i < n; i++) if (f(g, st, i)) o.push_back(i);
        return o;
    }
};

/*
Approach:
0/1/2 colors.
Time Complexity:
O(V+E)
Space Complexity:
O(V)
Key Idea:
Cycle unsafe.
*/
