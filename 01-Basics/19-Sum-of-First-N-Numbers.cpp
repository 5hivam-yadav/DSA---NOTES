/*
Problem: Sum of First N Numbers
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Basics
Statement: Given n, return the sum 1 + 2 + ... + n via recursion or the formula n(n+1)/2.
Sample Input: n = 10
Sample Output: 55
Explanation: 10 * 11 / 2 = 55.
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

int f(int n) {
    if (n == 0) return 0;
    return n + f(n - 1);
}
  // Formula: n*(n+1)/2 O(1).

int main() {
    int n = 10;

    auto ans = f(n);
    cout << ans << endl;
    return 0;
}

/*
Approach:
1. Base 0.
2. Return n + f(n-1).
Time Complexity:
O(n)
Space Complexity:
O(n) stack
Key Idea:
Parametrized recursion accumulates on return.
*/
