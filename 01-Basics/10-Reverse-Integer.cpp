/*
Problem: Reverse Integer
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Maths
Statement: Given a signed 32-bit integer x, return x with its digits reversed.
Return 0 on overflow outside [-2^31, 2^31 - 1]. Sample Input: x = 123 Sample
Output: 321 Explanation: Digits 1, 2, 3 become 3, 2, 1.
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
    int reverse(int x) {
        long long r = 0;
        while (x) {
            r = r * 10 + x % 10;
            x /= 10;
        }
        if (r < INT_MIN || r > INT_MAX)
            return 0;
        return (int)r;
    }
};

int main() {
    int x = 123;

    Solution sol;
    auto ans = sol.reverse(x);
    cout << ans << endl;
    return 0;
}

/*
Approach:
1. Pop digit, push to rev.
2. Clamp 32-bit.
Time Complexity:
O(log10 n)
Space Complexity:
O(1)
Key Idea:
Build reversed with overflow check.
*/
