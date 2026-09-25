/*
Problem: Scc Kosaraju
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Graph (BFS/DFS)
Statement: Given a directed graph, return its strongly connected components with Kosaraju (order + reverse DFS).
Sample Input: n = 5, edges = [[0,1],[1,2],[2,0],[1,3],[3,4]]
Sample Output: [[0,1,2],[3],[4]]
Explanation: Triangle forms one SCC; 3 and 4 are solo.
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

void o1(int u, vector<vector<int>>& g, vector<int>& v, vector<int>& o) {
    v[u] = 1;
    for (int x : g[u]) if (!v[x]) o1(x, g, v, o);
    o.push_back(u);
}
void o2(int u, vector<vector<int>>& r, vector<int>& v, vector<int>& c) {
    v[u] = 1;
    c.push_back(u);
    for (int x : r[u]) if (!v[x]) o2(x, r, v, c);
}

/*
Approach:
Order + reverse DFS.
Time Complexity:
O(V+E)
Space Complexity:
O(V+E)
Key Idea:
SCC reverse reach.
*/
