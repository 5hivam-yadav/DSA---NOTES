/*
Problem: Power n
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Maths
Statement: Given x and n, return x raised to n with fast exponentiation in O(log
n). Sample Input: x = 2, n = 10 Sample Output: 1024 Explanation: 2^10 = 1024.
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
    double myPow(double x, long long n) {
        if (n < 0) {
            x = 1 / x;
            n = -n;
        }
        double r = 1;
        while (n) {
            if (n & 1)
                r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
};

/*
Approach:
Square + multiply on set bit.
Time Complexity:
O(log n)
Space Complexity:
O(1)
Key Idea:
Binary exponent.
*/
