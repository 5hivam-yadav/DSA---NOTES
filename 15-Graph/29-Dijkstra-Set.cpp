/*
Problem: Dijkstra Set
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Shortest Path
Statement: Given a weighted graph with non-negative edges and source, return shortest distances using a set (ordered) for relaxations.
Sample Input: n = 4, edges 0-1(4), 0-2(1), 2-1(2), 1-3(1), s = 0
Sample Output: [0,3,1,4]
Explanation: Same distances as priority-queue Dijkstra.
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

vector<int> dijkSet(int n, vector<vector<pair<int, int>>>& g, int s, vector<int>& par) {
    const int INF = 1e9;
    vector<int> d(n, INF);
    par.assign(n, -1);
    d[s] = 0;
    set<pair<int, int>> st;
    st.insert({0, s});
    while (!st.empty()) {
        auto [c, u] = *st.begin();
        st.erase(st.begin());
        for (auto [v, w] : g[u]) if (d[v] > c + w) {
            st.erase({d[v], v});
            d[v] = c + w;
            par[v] = u;
            st.insert({d[v], v});
        }
    }
    return d;
}

/*
Approach:
Set decrease-key.
Time Complexity:
O(E log V)
Space Complexity:
O(V+E)
Key Idea:
Parent rebuilds path.
*/
