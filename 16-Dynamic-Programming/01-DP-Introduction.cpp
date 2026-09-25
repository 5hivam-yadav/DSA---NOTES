/*
Problem: Dynamic Programming Introduction
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Dynamic Programming
Statement: Given n, compute the n-th Fibonacci number three ways: memoised recursion, tabulation, and O(1)-space iteration.
Sample Input: n = 7
Sample Output: 13
Explanation: Recurrence F(n) = F(n-1) + F(n-2) reaches 13.
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

int fibM(int n, vector<int>& dp) {
    if (n <= 1) return n;
    if (dp[n] != -1) return dp[n];
    return dp[n] = fibM(n-1, dp) + fibM(n-2, dp);
}
int fibT(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        int c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n = 7;

    auto ans = fibT(n);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Memo top-down;
tab bottom-up.
Time Complexity:
O(n)
Space Complexity:
O(n)/O(1)
Key Idea:
Overlap + optimal substructure.
*/
