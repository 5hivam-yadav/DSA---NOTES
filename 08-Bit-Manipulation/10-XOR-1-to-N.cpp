/*
Problem: XOR 1 to N
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Bit Manipulation
Statement: Given n, return XOR of 1..n using the n%4 pattern (n, 1, n+1, 0).
Sample Input: n = 5
Sample Output: 1
Explanation: 1^2^3^4^5 = 1.
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

int xorN(int n) {
    if (n % 4 == 0) return n;
    if (n % 4 == 1) return 1;
    if (n % 4 == 2) return n + 1;
    return 0;
}
int xorLR(int l, int r) {
    return xorN(r) ^ xorN(l - 1);
}

/*
Approach:
n%4 pattern.
Time Complexity:
O(1)
Space Complexity:
O(1)
Key Idea:
Periodic XOR.
*/
