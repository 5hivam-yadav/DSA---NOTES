/*
Problem: Check Kth Bit
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Bit Manipulation
Statement: Given n and k (0-indexed), return true if the k-th bit of n is set
((n >> k) & 1). Sample Input: n = 13, k = 2 Sample Output: true Explanation: 13
is 1101; bit 2 is 1.
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

bool kth(int n, int k) { return (n >> k) & 1; }
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
