/*
Problem: Check Power of 2
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Maths
Statement: Given n, return true if n is a power of two (n > 0 and (n & (n-1)) == 0).
Sample Input: n = 16
Sample Output: true
Explanation: 16 is 10000 with a single set bit.
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
    bool isPowerOfTwo(int n) {
        return n > 0 && (n & (n - 1)) == 0;
    }
};

int main() {
    int n = 16;

    Solution sol;
    auto ans = sol.isPowerOfTwo(n);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
One bit check.
Time Complexity:
O(1)
Space Complexity:
O(1)
Key Idea:
Single 1-bit.
*/
