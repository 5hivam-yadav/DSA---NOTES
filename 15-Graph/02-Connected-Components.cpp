/*
Problem: Connected Components
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Graph (BFS/DFS)
Statement: Given an undirected graph, return the number of connected components (visited set + BFS/DFS).
Sample Input: n = 5, edges = [[0,1],[3,4]]
Sample Output: 3
Explanation: Components are {0,1}, {2}, {3,4}.
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

void dfs(int u, vector<vector<int>>& g, vector<int>& v) {
    v[u] = 1;
    for (int x : g[u]) if (!v[x]) dfs(x, g, v);
}
int comps(int n, vector<vector<int>>& g) {
    vector<int> v(n, 0);
    int c = 0;
    for (int i = 0; i < n; i++) if (!v[i]) {
        c++;
        dfs(i, g, v);
    }
    return c;
}

int main() {
    int n = 5;
    vector<vector<int>> edges = {{0, 1}, {3, 4}};

    auto ans = comps(n, edges);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Count DFS starts.
Time Complexity:
O(V+E)
Space Complexity:
O(V)
Key Idea:
Each start = component.
*/
