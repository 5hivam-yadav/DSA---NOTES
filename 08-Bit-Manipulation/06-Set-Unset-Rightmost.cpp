/*
Problem: Set Unset Rightmost
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Bit Manipulation
Statement: Given n, set the rightmost unset bit; if all bits set, leave n
unchanged. Sample Input: n = 12 (1100) Sample Output: 13 (1101) Explanation:
Lowest 0-bit is bit 0; setting it gives 1101.
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

int setRightmostUnset(int n) { return n | (n + 1); }
int unsetRightmostSet(int n) { return n & (n - 1); }

/*
Approach:
n+1 flips trailing 1s/0s.
Time Complexity:
O(1)
Space Complexity:
O(1)
Key Idea:
Carry trick.
*/
