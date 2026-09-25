/*
Problem: Disjoint Set Union
Platform: GFG / LeetCode
Problem Number: -
Difficulty: Medium
Pattern: DSU
Statement: Implement DSU with path compression and union by rank/size; find returns the set representative.
Sample Input: unions (0,1),(1,2), find(0)==find(2)
Sample Output: true
Explanation: 0, 1, 2 share one root after unions.
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

struct DSU {
    vector<int> p, r, s;
    DSU(int n): p(n), r(n, 0), s(n, 1) {
        iota(p.begin(), p.end(), 0);
    }
    int f(int x) {
        return p[x] == x ? x : p[x] = f(p[x]);
    }
    void uRank(int a, int b) {
        a = f(a);
        b = f(b);
        if (a == b) return;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
    }
    void uSize(int a, int b) {
        a = f(a);
        b = f(b);
        if (a == b) return;
        if (s[a] < s[b]) swap(a, b);
        p[b] = a;
        s[a] += s[b];
    }
};

/*
Approach:
Path + rank/size.
Time Complexity:
Alpha amortized
Space Complexity:
O(n)
Key Idea:
Union-find base.
*/
