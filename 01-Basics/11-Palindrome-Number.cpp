/*
Problem: Palindrome Number
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Maths
Statement: Given an integer x, return true if x reads the same forwards and
backwards, otherwise false. Negatives are never palindromes. Sample Input: x =
121 Sample Output: true Explanation: 121 reversed is still 121.
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

class Solution {
  public:
    bool isPalindrome(int x) {
        if (x < 0)
            return false;
        long long r = 0, t = x;
        while (t) {
            r = r * 10 + t % 10;
            t /= 10;
        }
        return r == x;
    }
};

int main() {
    int x = 121;

    Solution sol;
    auto ans = sol.isPalindrome(x);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
1. Negative false.
2. Reverse, compare.
Time Complexity:
O(log10 n)
Space Complexity:
O(1)
Key Idea:
Reverse equals original.
*/
