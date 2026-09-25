/*
Problem: Palindrome Partitioning
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Backtracking
Statement: Given s, return all ways to split it so every piece is a palindrome (backtrack + palindrome check).
Sample Input: s = "aab"
Sample Output: [["a","a","b"],["aa","b"]]
Explanation: Both splits use only palindromes.
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
    vector<vector<string>> ans;
    vector<string> ds;
    bool pal(const string& s, int l, int r) {
        while (l < r) if (s[l++] != s[r--]) return false;
        return true;
    }
    void f(int i, const string& s) {
        if (i == (int)s.size()) {
            ans.push_back(ds);
            return;
        }
        for (int j = i; j < (int)s.size(); j++) if (pal(s, i, j)) {
            ds.push_back(s.substr(i, j - i + 1));
            f(j + 1, s);
            ds.pop_back();
        }
    }
    vector<vector<string>> partition(string s) {
        f(0, s);
        return ans;
    }
};

int main() {
    string s = "aab";

    Solution sol;
    auto ans = sol.partition(s);
    for (int i = 0; i < (int)ans.size(); i++) {
        for (int j = 0; j < (int)ans[i].size(); j++) cout << ans[i][j] << " ";
        cout << endl;
    }
    return 0;
}

/*
Approach:
Cut at palindromes.
Time Complexity:
O(2^n n)
Space Complexity:
O(n)
Key Idea:
Partition tree.
*/
