/*
Problem: Bellman Ford
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Shortest Path
Statement: Given n nodes, an edge list and source, return shortest distances with n-1 relaxations; flag a negative cycle if one more relaxation succeeds.
Sample Input: n = 4, edges (0->1:1, 1->2:2, 2->3:3), s = 0
Sample Output: [0,1,3,6]
Explanation: Edges settle after at most 3 rounds.
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

vector<long long> bellman(int n, vector<tuple<int, int, int>>& e, int s, bool& neg) {
    const long long INF = 4e18;
    vector<long long> d(n, INF);
    d[s] = 0;
    for (int i = 0; i < n - 1; i++) {
        bool up = false;
        for (auto& [u, v, w] : e) {
            if (d[u] != INF && d[v] > d[u] + w) {
                d[v] = d[u] + w;
                up = true;
            }
        }
        if (!up) break;
    }
    neg = false;
    for (auto& [u, v, w] : e) if (d[u] != INF && d[v] > d[u] + w) neg = true;
    return d;
}

/*
Approach:
V-1 relax + detect.
Time Complexity:
O(VE)
Space Complexity:
O(V)
Key Idea:
Negative edges ok.
*/
