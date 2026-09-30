/*
Problem: Longest Substring K Distinct
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Sliding Window
Statement: Given s and k, return the length of the longest substring with at
most k distinct characters. Sample Input: s = "eceba", k = 2 Sample Output: 3
Explanation: "ece" uses two distinct letters.
*/
#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

int longestK(string s, int k) {
    if (k == 0)
        return 0;
    unordered_map<char, int> f;
    int l = 0, b = 0;
    for (int r = 0; r < (int)s.size(); r++) {
        f[s[r]]++;
        while ((int)f.size() > k) {
            if (--f[s[l]] == 0)
                f.erase(s[l]);
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
