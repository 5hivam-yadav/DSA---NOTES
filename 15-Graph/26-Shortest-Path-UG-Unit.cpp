/*
Problem: Shortest Path Ug Unit
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Shortest Path
Statement: Given an unweighted undirected graph and source, return shortest distances in edges via BFS.
Sample Input: n = 4, edges = [[0,1],[1,2],[2,3]], s = 0
Sample Output: [0,1,2,3]
Explanation: BFS layers give distances 0..3.
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

vector<int> shortUG(int n, vector<vector<int>>& g, int s) {
    vector<int> d(n, -1);
    queue<int> q;
    q.push(s);
    d[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) if (d[v] == -1) {
            d[v] = d[u] + 1;
            q.push(v);
        }
    }
    return d;
}

int main() {
    int n = 4;
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 3}};
    int s = 0;

    auto ans = shortUG(n, edges, s);
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
BFS distance.
Time Complexity:
O(V+E)
Space Complexity:
O(V)
Key Idea:
Unweighted BFS.
*/
