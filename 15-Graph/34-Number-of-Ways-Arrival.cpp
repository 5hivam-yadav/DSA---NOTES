/*
Problem: Number of Ways Arrival
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Shortest Path
Statement: Given weighted roads and n nodes, count shortest paths from 0 to n-1 modulo 1e9+7 (Dijkstra + path counts).
Sample Input: n = 7, sample roads
Sample Output: 4
Explanation: Four distinct routes share the minimum time.
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
    const int M = 1000000007;
    int countPaths(int n, vector<vector<int>>& r) {
        vector<vector<pair<int, int>>> g(n);
        for (auto& e : r) {
            g[e[0]].push_back({e[1], e[2]});
            g[e[1]].push_back({e[0], e[2]});
        }
        vector<long long> d(n, LLONG_MAX), ways(n, 0);
        d[0] = 0;
        ways[0] = 1;
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        pq.push({0, 0});
        while (!pq.empty()) {
            auto [c, u] = pq.top();
            pq.pop();
            if (c != d[u]) continue;
            for (auto [v, w] : g[u]) {
                if (d[v] > c + w) {
                    d[v] = c + w;
                    ways[v] = ways[u];
                    pq.push({d[v], v});
                }
                else if (d[v] == c + w) ways[v] = (ways[v] + ways[u]) % M;
            }
        }
        return (int)ways[n-1];
    }
};

/*
Approach:
Dijkstra + count.
Time Complexity:
O(E log V)
Space Complexity:
O(V+E)
Key Idea:
Equal-dist adds ways.
*/
