/*
Problem: Pascals Triangle Variant1
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP on Grids
Statement: Given r (1-indexed), return the r-th row of Pascal's triangle using nCr computed iteratively.
Sample Input: r = 5
Sample Output: [1, 4, 6, 4, 1]
Explanation: Row 5 of Pascal's triangle is 1 4 6 4 1.
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

long long nCr(int n, int r) {
    if (r > n) return 0;
    if (r > n - r) r = n - r;
    long long ans = 1;
    for (int i = 0; i < r; i++) ans = ans * (n - i) / (i + 1);
    return ans;
}

/*
Approach:
Multiplicative formula.
Time Complexity:
O(r)
Space Complexity:
O(1)
Key Idea:
Avoid factorials.
*/
