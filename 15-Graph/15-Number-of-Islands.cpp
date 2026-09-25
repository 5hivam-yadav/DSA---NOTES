/*
Problem: Number of Islands
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Graph (BFS/DFS)
Statement: Given a grid of land (1) and water (0), count the islands (4-connected land groups) with DFS/BFS.
Sample Input: grid = [["1","1","0"],["1","0","0"],["0","0","1"]]
Sample Output: 2
Explanation: Two separate land groups exist.
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
    void f(vector<vector<char>>& g, int i, int j) {
        int R = g.size(), C = g[0].size();
        if (i < 0 || j < 0 || i >= R || j >= C || g[i][j] != '1') return;
        g[i][j] = '0';
        f(g, i+1, j);
        f(g, i-1, j);
        f(g, i, j+1);
        f(g, i, j-1);
    }
    int numIslands(vector<vector<char>>& g) {
        if (g.empty()) return 0;
        int c = 0;
        for (size_t i = 0; i < g.size(); i++) for (size_t j = 0; j < g[0].size(); j++) if (g[i][j] == '1') {
            c++;
            f(g, i, j);
        }
        return c;
    }
};

/*
Approach:
Sink each island.
Time Complexity:
O(RC)
Space Complexity:
O(RC)
Key Idea:
Each start = island.
*/
