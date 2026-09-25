/*
Problem: Scc Tarjan
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Graph (BFS/DFS)
Statement: Given a directed graph, return its strongly connected components with Tarjan low-link in one DFS pass.
Sample Input: n = 5, edges = [[0,1],[1,2],[2,0],[1,3],[3,4]]
Sample Output: [[0,1,2],[3],[4]]
Explanation: Same SCCs as Kosaraju.
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

int ti = 0;
vector<int> dd, ll;
vector<char> st;
vector<int> s;
void f3(int u, vector<vector<int>>& g, vector<vector<int>>& ans) {
    dd[u] = ll[u] = ti++;
    s.push_back(u);
    st[u] = 1;
    for (int v : g[u]) {
        if (dd[v] == -1) {
            f3(v, g, ans);
            ll[u] = min(ll[u], ll[v]);
        }
        else if (st[v]) ll[u] = min(ll[u], dd[v]);
    }
    if (ll[u] == dd[u]) {
        vector<int> c;
        while (1) {
            int x = s.back();
            s.pop_back();
            st[x] = 0;
            c.push_back(x);
            if (x == u) break;
        }
        ans.push_back(c);
    }
}

/*
Approach:
Stack + lowlink.
Time Complexity:
O(V+E)
Space Complexity:
O(V)
Key Idea:
Root pops SCC.
*/
