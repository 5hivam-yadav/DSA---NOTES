/*
Problem: Divide without Division
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Bit Manipulation
Statement: Given dividend and divisor, return the truncated quotient without
using * / % (bit shifts and subtraction). Sample Input: dividend = 10, divisor =
3 Sample Output: 3 Explanation: 10 / 3 truncates to 3.
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
    int divide(int a, int b) {
        if (a == INT_MIN && b == -1)
            return INT_MAX;
        long long x = llabs((long long)a), y = llabs((long long)b), ans = 0;
        for (int i = 31; i >= 0; i--) {
            if ((x >> i) >= y) {
                ans += 1LL << i;
                x -= y << i;
            }
        }
        return ((a < 0) ^ (b < 0)) ? -(int)ans : (int)ans;
    }
};

int main() {
    int dividend = 10;
    int divisor = 3;

    Solution sol;
    auto ans = sol.divide(dividend, divisor);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Subtract shifted divisor.
Time Complexity:
O(32)
Space Complexity:
O(1)
Key Idea:
Binary long division.
*/
