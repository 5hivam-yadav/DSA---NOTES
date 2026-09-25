/*
Problem: Number of Provinces
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DSU
Statement: Given an adjacency matrix of cities, count the provinces (connected components) with DFS/BFS or DSU.
Sample Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
Sample Output: 2
Explanation: {0,1} connect; {2} is alone.
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
    void dfs(int u, vector<vector<int>>& g, vector<int>& v) {
        v[u] = 1;
        for (int x : g[u]) if (!v[x]) dfs(x, g, v);
    }
    int findCircleNum(vector<vector<int>>& m) {
        int n = m.size();
        vector<vector<int>> g(n);
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (m[i][j] && i != j) g[i].push_back(j);
        vector<int> v(n, 0);
        int c = 0;
        for (int i = 0; i < n; i++) if (!v[i]) {
            c++;
            dfs(i, g, v);
        }
        return c;
    }
};

/*
Approach:
Matrix to list + comps.
Time Complexity:
O(n^2)
Space Complexity:
O(n)
Key Idea:
Province = component.
*/
