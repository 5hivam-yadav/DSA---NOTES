/*
Problem: Fibonacci Number
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Recursion / DP
Statement: Given n, return the n-th Fibonacci number with F(0)=0, F(1)=1, F(n)=F(n-1)+F(n-2).
Sample Input: n = 7
Sample Output: 13
Explanation: Sequence reaches 13 at index 7.
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
    int fib(int n) {
        if (n <= 1) return n;
        int a = 0, b = 1;
        for (int i = 2; i <= n; i++) {
            int c = a + b;
            a = b;
            b = c;
        }
        return b;
    }
};
  // Brute recursion O(2^n); memo O(n)/O(n); above O(n)/O(1).

int main() {
    int n = 7;

    Solution sol;
    auto ans = sol.fib(n);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Optimal iterative.
1. a=0, b=1 roll forward.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Only previous two matter.
*/
