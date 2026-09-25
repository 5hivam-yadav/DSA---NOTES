/*
Problem: Count Set Bits
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Bit Manipulation
Statement: Given n, return the number of 1 bits (Brian Kernighan: n &= n-1 per set bit).
Sample Input: n = 13
Sample Output: 3
Explanation: 1101 has three 1s.
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
    int hammingWeight(int n) {
        int c = 0;
        while (n) {
            n &= n - 1;
            c++;
        }
        return c;
    }
};
  // builtin: __builtin_popcount(n).

int main() {
    int n = 13;

    Solution sol;
    auto ans = sol.hammingWeight(n);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Clear lowest set.
Time Complexity:
O(k)
Space Complexity:
O(1)
Key Idea:
x&(x-1).
*/
