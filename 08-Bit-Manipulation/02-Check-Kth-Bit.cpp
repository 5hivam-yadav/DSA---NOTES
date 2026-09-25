/*
Problem: Check Kth Bit
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Bit Manipulation
Statement: Given n and k (0-indexed), return true if the k-th bit of n is set ((n >> k) & 1).
Sample Input: n = 13, k = 2
Sample Output: true
Explanation: 13 is 1101; bit 2 is 1.
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

bool kth(int n, int k) {
    return (n >> k) & 1;
}
  // Alt: (n & (1 << k)) != 0.

int main() {
    int n = 13;
    int k = 2;

    auto ans = kth(n, k);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
Shift and &1.
Time Complexity:
O(1)
Space Complexity:
O(1)
Key Idea:
Mask bit.
*/
