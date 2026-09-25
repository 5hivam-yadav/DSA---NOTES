/*
Problem: Shortest Palindrome
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Strings
Statement: Given s, return the shortest palindrome formed by prepending characters (KMP on s + '#' + reverse).
Sample Input: s = "aacecaaa"
Sample Output: "aaacecaaa"
Explanation: Prepending "aa" completes the palindrome.
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
    string shortestPalindrome(string s) {
        string rev = s;
        reverse(rev.begin(), rev.end());
        string t = s + "#" + rev;
        int n = (int)t.size();
        vector<int> lps(n, 0);
        for (int i = 1; i < n; i++) {
            int j = lps[i - 1];
            while (j > 0 && t[i] != t[j]) j = lps[j - 1];
            if (t[i] == t[j]) j++;
            lps[i] = j;
        }
        string add = rev.substr(0, (int)s.size() - lps.back());
        return add + s;
    }
};

int main() {
    string s = "aacecaaa";

    Solution sol;
    auto ans = sol.shortestPalindrome(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Longest palindromic prefix = LPS of s#reverse(s).
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Prepend reverse of unmatched suffix.
*/
