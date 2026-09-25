/*
Problem: Valid Anagram
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Hashing
Statement: Given strings s and t, return true if t is an anagram of s (same character counts).
Sample Input: s = "anagram", t = "nagaram"
Sample Output: true
Explanation: Both use the same letters with the same counts.
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
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;
        int c[26] = {0};
        for (char x : s) c[x - 'a']++;
        for (char x : t) if (--c[x - 'a'] < 0) return false;
        return true;
    }
};

int main() {
    string s = "anagram";
    string t = "nagaram";

    Solution sol;
    auto ans = sol.isAnagram(s, t);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
26-count.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Same counts.
*/
