/*
Problem: Number of Provinces Disjoint Set Union
Platform: GFG / LeetCode
Problem Number: -
Difficulty: Medium
Pattern: DSU
Statement: Given an adjacency matrix of cities, count the provinces (connected components) with a disjoint-set union.
Sample Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
Sample Output: 2
Explanation: Union of 0 and 1 leaves two groups: {0,1} and {2}.
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
    vector<int> p;
    int f(int x) {
        return p[x] == x ? x : p[x] = f(p[x]);
    }
    int findCircleNum(vector<vector<int>>& m) {
        int n = m.size();
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) if (m[i][j]) {
            int a = f(i), b = f(j);
            if (a != b) p[b] = a;
        }
        int c = 0;
        for (int i = 0; i < n; i++) if (f(i) == i) c++;
        return c;
    }
};

/*
Approach:
Union connected.
Time Complexity:
O(n^2 alpha)
Space Complexity:
O(n)
Key Idea:
Count roots.
*/
