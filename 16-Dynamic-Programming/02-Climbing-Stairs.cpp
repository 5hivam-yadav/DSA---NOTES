/*
Problem: Climbing Stairs
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: DP - 1D
Statement: Given n steps, return the number of ways to climb taking 1 or 2 steps
at a time. Sample Input: n = 5 Sample Output: 8 Explanation: Ways follow
1,2,3,5,8 for n = 1..5.
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
    int climbStairs(int n) {
        if (n <= 2)
            return n;
        int a = 1, b = 2;
        for (int i = 3; i <= n; i++) {
            int c = a + b;
            a = b;
            b = c;
        }
        return b;
    }
};
// 1 Recursion O(2^n). 2 Memo O(n)/O(n). 3 Tab O(n)/O(n). 4 Above O(n)/O(1).

int main() {
    int n = 5;

    Solution sol;
    auto ans = sol.climbStairs(n);
    cout << ans << endl;
    return 0;
}

/*
Approach:
f(n)=f(n-1)+f(n-2).
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Fib steps.
*/
