/*
Problem: Kruskal Minimum Spanning Tree
Platform: GFG / LeetCode
Problem Number: -
Difficulty: Medium
Pattern: MST
Statement: Given weighted edges, return the MST weight by sorting edges and uniting components with DSU.
Sample Input: n = 4, edges weights [1,2,3,4,5]
Sample Output: minimum total weight
Explanation: Cheapest acyclic edges connect all nodes.
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

struct DSU2 {
    vector<int> p;
    DSU2(int n): p(n) {
        iota(p.begin(), p.end(), 0);
    }
    int f(int x) {
        return p[x] == x ? x : p[x] = f(p[x]);
    }
    bool u(int a, int b) {
        a = f(a);
        b = f(b);
        if (a == b) return false;
        p[b] = a;
        return true;
    }
};
int kruskal(int n, vector<tuple<int, int, int>>& e) {
    sort(e.begin(), e.end());
    DSU2 d(n);
    int c = 0;
    for (auto& [w, u, v] : e) if (d.u(u, v)) c += w;
    return c;
}

/*
Approach:
Sort edges + DSU.
Time Complexity:
O(E log E)
Space Complexity:
O(V)
Key Idea:
Greedy safe edges.
*/
