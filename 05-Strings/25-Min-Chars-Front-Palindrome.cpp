/*
Problem: Min Chars Front Palindrome
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Strings
Statement: Given a string, return the minimum characters to prepend to make it a palindrome (KMP on s + '#' + reverse).
Sample Input: s = "AACECAAAA"
Sample Output: 2
Explanation: Prepending "AA" gives "AAAACECAAAA".
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

int minCharsToMakePalindrome(const string& s) {
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
    return (int)s.size() - lps.back();
}

int main() {
    string s = "AACECAAAA";

    auto ans = minCharsToMakePalindrome(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Longest palindromic prefix via KMP;
add rest at front.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Same LPS trick as shortest palindrome.
*/
