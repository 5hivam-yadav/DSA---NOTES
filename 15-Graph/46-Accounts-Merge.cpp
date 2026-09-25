/*
Problem: Accounts Merge
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DSU
Statement: Given accounts (name + emails), merge accounts sharing any email via DSU over emails and return grouped emails sorted.
Sample Input: accounts = [["John","a@x","b@x"],["John","b@x","c@x"]]
Sample Output: [["John","a@x","b@x","c@x"]]
Explanation: Shared b@x merges both accounts.
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
    vector<vector<string>> accountsMerge(vector<vector<string>>& a) {
        int n = a.size();
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        unordered_map<string, int> m;
        for (int i = 0; i < n; i++) for (size_t j = 1; j < a[i].size(); j++) {
            if (!m.count(a[i][j])) m[a[i][j]] = i;
            else {
                int x = f(i), y = f(m[a[i][j]]);
                if (x != y) p[y] = x;
            }
        }
        unordered_map<int, set<string>> g;
        for (auto& kv : m) g[f(kv.second)].insert(kv.first);
        vector<vector<string>> r;
        for (auto& kv : g) {
            vector<string> e;
            e.push_back(a[kv.first][0]);
            for (auto& s : kv.second) e.push_back(s);
            r.push_back(e);
        }
        return r;
    }
};

/*
Approach:
Union shared emails.
Time Complexity:
O(N alpha)
Space Complexity:
O(N)
Key Idea:
Email to owner.
*/
