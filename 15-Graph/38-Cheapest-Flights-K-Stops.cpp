/*
Problem: Cheapest Flights K Stops
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Shortest Path
Statement: Given flights (from,to,price), src, dst and k, return the cheapest price with at most k stops (Bellman-Ford limited to k+1 rounds).
Sample Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], k = 1
Sample Output: 200
Explanation: 0->1->2 costs 200 with one stop.
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
    int findCheapestPrice(int n, vector<vector<int>>& f, int s, int t, int k) {
        const int INF = 1e9;
        vector<int> d(n, INF);
        d[s] = 0;
        for (int i = 0; i <= k; i++) {
            vector<int> nd = d;
            for (auto& e : f) {
                if (d[e[0]] != INF) nd[e[1]] = min(nd[e[1]], d[e[0]] + e[2]);
            }
            d = nd;
        }
        return d[t] == INF ? -1 : d[t];
    }
};

/*
Approach:
K+1 Bellman rounds.
Time Complexity:
O(K E)
Space Complexity:
O(n)
Key Idea:
Stops = rounds.
*/
