/*
Problem: Bipartite Check BFS
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Graph (BFS/DFS)
Statement: Given an undirected graph, return true if it is bipartite (2-colourable) using BFS colouring.
Sample Input: graph = [[1,3],[0,2],[1,3],[0,2]]
Sample Output: true
Explanation: Even cycle colours alternate cleanly.
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
    bool isBipartite(vector<vector<int>>& g) {
        int n = g.size();
        vector<int> c(n, -1);
        for (int s = 0; s < n; s++) {
            if (c[s] != -1) continue;
            queue<int> q;
            q.push(s);
            c[s] = 0;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : g[u]) {
                    if (c[v] == -1) {
                        c[v] = c[u] ^ 1;
                        q.push(v);
                    }
                    else if (c[v] == c[u]) return false;
                }
            }
        }
        return true;
    }
};

int main() {
    vector<vector<int>> graph = {{1, 3}, {0, 2}, {1, 3}, {0, 2}};

    Solution sol;
    auto ans = sol.isBipartite(graph);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
2-color BFS.
Time Complexity:
O(V+E)
Space Complexity:
O(V)
Key Idea:
Odd cycle fails.
*/
