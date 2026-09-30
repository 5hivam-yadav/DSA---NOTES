/*
Problem: Bipartite Check DFS
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Graph (BFS/DFS)
Statement: Given an undirected graph, return true if it is bipartite using DFS
colouring. Sample Input: graph = [[1,3],[0,2],[1,3],[0,2]] Sample Output: true
Explanation: No odd cycle forces a clash.
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

class Solution {
  public:
    bool f(vector<vector<int>> &g, vector<int> &c, int u) {
        for (int v : g[u]) {
            if (c[v] == -1) {
                c[v] = c[u] ^ 1;
                if (!f(g, c, v))
                    return false;
            } else if (c[v] == c[u])
                return false;
        }
        return true;
    }
    bool isBipartite(vector<vector<int>> &g) {
        int n = g.size();
        vector<int> c(n, -1);
        for (int i = 0; i < n; i++) {
            if (c[i] == -1) {
                c[i] = 0;
                if (!f(g, c, i))
                    return false;
            }
        }
        return true;
    }
};

/*
Approach:
Same 2-color DFS.
Time Complexity:
O(V+E)
Space Complexity:
O(V)
Key Idea:
Recur coloring.
*/
