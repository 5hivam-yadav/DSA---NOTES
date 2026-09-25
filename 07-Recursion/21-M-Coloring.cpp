/*
Problem: M Coloring
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Backtracking
Statement: Given a graph and m colours, decide if adjacent nodes can always differ (backtrack with validity check).
Sample Input: n = 4, edges triangle + tail, m = 3
Sample Output: true
Explanation: Three colours suffice for this graph.
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

bool okC(int v, vector<vector<int>>& g, vector<int>& col, int c) {
    for (int u : g[v]) if (col[u] == c) return false;
    return true;
}
bool f(int v, vector<vector<int>>& g, vector<int>& col, int m) {
    if (v == (int)g.size()) return true;
    for (int c = 1; c <= m; c++) if (okC(v, g, col, c)) {
        col[v] = c;
        if (f(v + 1, g, col, m)) return true;
        col[v] = 0;
    }
    return false;
}

int main() {
    int n = 4, m = 3;
    vector<vector<int>> g(n);
    g[0] = {1, 2};
    g[1] = {0, 2};
    g[2] = {0, 1, 3};
    g[3] = {2};
    vector<int> col(n, 0);
    cout << (f(0, g, col, m) ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
Try colors + undo.
Time Complexity:
O(m^V)
Space Complexity:
O(V)
Key Idea:
Adjacency check.
*/
