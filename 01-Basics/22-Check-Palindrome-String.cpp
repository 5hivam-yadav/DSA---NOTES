/*
Problem: Check Palindrome String
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Basics
Statement: Given a string, return true if it reads the same forwards and
backwards (two-pointer or recursive check). Sample Input: s = "madam" Sample
Output: true Explanation: m-a-d-a-m mirrors exactly.
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

bool pal(const string &s, int l, int r) {
    if (l >= r)
        return true;
    if (s[l] != s[r])
        return false;
    return pal(s, l + 1, r - 1);
}

/*
Approach:
1. Mismatch false.
2. Shrink both ends.
Time Complexity:
O(n)
Space Complexity:
O(n) stack
Key Idea:
Mirror compare from outside in.
*/
