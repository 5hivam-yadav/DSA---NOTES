/*
Problem: Pow X n
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Recursion
Statement: Given x and n, return x raised to n in O(log |n|) with fast exponentiation, handling negative n.
Sample Input: x = 2.0, n = 10
Sample Output: 1024.0
Explanation: 2^10 = 1024.
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
    double myPow(double x, long long n) {
        if (n < 0) return 1.0 / myPow(x, -n);
        if (n == 0) return 1;
        double h = myPow(x, n / 2);
        return n % 2 == 0 ? h * h : h * h * x;
    }
};

int main() {
    double x = 2.0;
    long long n = 10;
    Solution sol;
    cout << sol.myPow(x, n) << endl;
    return 0;
}

/*
Approach:
Half + square.
Time Complexity:
O(log n)
Space Complexity:
O(log n)
Key Idea:
Binary exponent.
*/
