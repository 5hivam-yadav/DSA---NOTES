/*
Problem: Single Number I
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Bit Manipulation
Statement: Given an array where every element appears twice except one, return that single one with XOR.
Sample Input: nums = [4, 1, 2, 1, 2]
Sample Output: 4
Explanation: Pairs cancel in XOR, leaving 4.
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
    int singleNumber(vector<int>& a) {
        int x = 0;
        for (int v : a) x ^= v;
        return x;
    }
};

int main() {
    vector<int> nums = {4, 1, 2, 1, 2};

    Solution sol;
    auto ans = sol.singleNumber(nums);
    cout << ans << endl;
    return 0;
}

/*
Approach:
XOR all.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Pairs cancel.
*/
