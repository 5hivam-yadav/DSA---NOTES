/*
Problem: Topo Sort DFS
Platform: GFG / Striver A2Z
Problem Number: -
Difficulty: Medium
Pattern: Topological Sort
Statement: Given a DAG, return a topological order using DFS post-order (reversed finish times).
Sample Input: n = 4, edges = [[0,1],[0,2],[1,3],[2,3]]
Sample Output: [0,2,1,3] (any valid order)
Explanation: Every edge points forward in the order.
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

void f(int u, vector<vector<int>>& g, vector<int>& v, vector<int>& o) {
    v[u] = 1;
    for (int x : g[u]) if (!v[x]) f(x, g, v, o);
    o.push_back(u);
}
vector<int> topo(int n, vector<vector<int>>& g) {
    vector<int> v(n, 0), o;
    for (int i = 0; i < n; i++) if (!v[i]) f(i, g, v, o);
    reverse(o.begin(), o.end());
    return o;
}

int main() {
    int n = 4;
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 3}, {2, 3}};

    auto ans = topo(n, edges);
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Postorder reverse.
Time Complexity:
O(V+E)
Space Complexity:
O(V)
Key Idea:
DAG only.
*/
