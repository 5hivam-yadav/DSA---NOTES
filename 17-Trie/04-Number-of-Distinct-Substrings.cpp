/*
Problem: Number of Distinct Substrings
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Trie
Statement: Given s, count its distinct substrings (insert all suffixes into a trie / suffix set).
Sample Input: s = "abab"
Sample Output: 7
Explanation: "a","b","ab","ba","aba","bab","abab" are distinct.
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

struct S {
    int ch[26];
    S() {
        memset(ch, -1, sizeof ch);
    }
};
int distinctSubstr(string s) {
    vector<S> t(1);
    int n = s.size(), ans = 0;
    for (int i = 0; i < n; i++) {
        int v = 0;
        for (int j = i; j < n; j++) {
            int c = s[j] - 'a';
            if (t[v].ch[c] == -1) {
                t[v].ch[c] = t.size();
                t.push_back(S());
                ans++;
            }
            v = t[v].ch[c];
        }
    }
    return ans;
}
  // Suffix automaton O(n) also.

int main() {
    string s = "abab";

    auto ans = distinctSubstr(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Insert all suffixes.
Time Complexity:
O(n^2)
Space Complexity:
O(n^2)
Key Idea:
New node = new substring.
*/
