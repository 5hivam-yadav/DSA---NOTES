/*
Problem: Single Number II
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Bit Manipulation
Statement: Given an array where every element appears three times except one,
return that single one with bit counting. Sample Input: nums = [2, 2, 3, 2]
Sample Output: 3
Explanation: Only 3 appears once.
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

class Solution {
  public:
    int singleNumber(vector<int> &a) {
        int ans = 0;
        for (int b = 0; b < 32; b++) {
            int c = 0;
            for (int x : a)
                if ((x >> b) & 1)
                    c++;
            if (c % 3)
                ans |= (1 << b);
        }
        return ans;
    }
};
// Ones/twos state machine O(n)/O(1) also.

int main() {
    vector<int> nums = {2, 2, 3, 2};

    Solution sol;
    auto ans = sol.singleNumber(nums);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Bit-count mod 3.
Time Complexity:
O(32n)
Space Complexity:
O(1)
Key Idea:
Mask per bit.
*/
