/*
Problem: Most Stones Removed
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: DSU
Statement: Given stone coordinates sharing rows/columns, return max removable stones = stones - connected components (DSU on rows+cols).
Sample Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
Sample Output: 5
Explanation: All 6 connect as one component, so 6-1 = 5.
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
    int removeStones(vector<vector<int>>& s) {
        int n = s.size();
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) if (s[i][0] == s[j][0] || s[i][1] == s[j][1]) {
            int a = f(i), b = f(j);
            if (a != b) p[b] = a;
        }
        unordered_set<int> r;
        for (int i = 0; i < n; i++) r.insert(f(i));
        return n - (int)r.size();
    }
};

/*
Approach:
n - components.
Time Complexity:
O(n^2 alpha)
Space Complexity:
O(n)
Key Idea:
Row/col connectivity.
*/
