/*
Problem: Pascals Triangle Variant1
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP on Grids
Statement: Given r (1-indexed), return the r-th row of Pascal's triangle using
nCr computed iteratively. Sample Input: r = 5 Sample Output: [1, 4, 6, 4, 1]
Explanation: Row 5 of Pascal's triangle is 1 4 6 4 1.
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

long long nCr(int n, int r) {
    if (r > n)
        return 0;
    if (r > n - r)
        r = n - r;
    long long ans = 1;
    for (int i = 0; i < r; i++)
        ans = ans * (n - i) / (i + 1);
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
