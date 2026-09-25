/*
Problem: Longest Substring K Distinct
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Sliding Window
Statement: Given s and k, return the length of the longest substring with at most k distinct characters.
Sample Input: s = "eceba", k = 2
Sample Output: 3
Explanation: "ece" uses two distinct letters.
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

int longestK(string s, int k) {
    if (k == 0) return 0;
    unordered_map<char, int> f;
    int l = 0, b = 0;
    for (int r = 0; r < (int)s.size(); r++) {
        f[s[r]]++;
        while ((int)f.size() > k) {
            if (--f[s[l]] == 0) f.erase(s[l]);
            l++;
        }
        b = max(b, r - l + 1);
    }
    return b;
}

int main() {
    string s = "eceba";
    int k = 2;

    auto ans = longestK(s, k);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Distinct <= k.
Time Complexity:
O(n) avg
Space Complexity:
O(k)
Key Idea:
Freq window.
*/
