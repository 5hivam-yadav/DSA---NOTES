/*
Problem: Rabin Karp
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: String Matching
Statement: Given text and pattern, find all occurrences with a rolling hash (Rabin-Karp), verifying hits to avoid collisions.
Sample Input: text = "ababcabc", pattern = "abc"
Sample Output: [2, 5]
Explanation: "abc" occurs at indices 2 and 5.
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

vector<int> rabinKarp(const string& text, const string& pat) {
    const long long MOD = 1000000007LL, BASE = 256LL;
    int n = (int)text.size(), m = (int)pat.size();
    vector<int> ans;
    if (m > n) return ans;
    long long hpat = 0, hwin = 0, pw = 1;
    for (int i = 0; i < m; i++) {
        hpat = (hpat * BASE + (unsigned char)pat[i]) % MOD;
        hwin = (hwin * BASE + (unsigned char)text[i]) % MOD;
        if (i) pw = (pw * BASE) % MOD;
    }
    for (int i = 0; i + m <= n; i++) {
        if (hwin == hpat && text.compare(i, m, pat) == 0) ans.push_back(i);
        if (i + m < n) {
            hwin = (hwin - (unsigned char)text[i] * pw % MOD + MOD) % MOD;
            hwin = (hwin * BASE + (unsigned char)text[i + m]) % MOD;
        }
    }
    return ans;
}

int main() {
    string text = "ababcabc";
    string pattern = "abc";

    auto ans = rabinKarp(text, pattern);
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Rolling hash, verify hits to kill collisions.
Time Complexity:
O(n+m) average
Space Complexity:
O(1) extra
Key Idea:
Subtract outgoing char * BASE^(m-1).
*/
