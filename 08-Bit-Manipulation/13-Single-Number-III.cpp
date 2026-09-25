/*
Problem: Single Number III
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Bit Manipulation
Statement: Given an array where every element appears twice except two, return both singletons using rightmost set bit.
Sample Input: nums = [1, 2, 1, 3, 2, 5]
Sample Output: [3, 5]
Explanation: Pairs cancel; 3 and 5 remain.
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
    vector<int> singleNumber(vector<int>& a) {
        int x = 0;
        for (int v : a) x ^= v;
        int d = x & -x;
        int p = 0, q = 0;
        for (int v : a) {
            if (v & d) p ^= v;
            else q ^= v;
        }
        return { p, q};
    }
};

int main() {
    vector<int> nums = {1, 2, 1, 3, 2, 5};

    Solution sol;
    auto ans = sol.singleNumber(nums);
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Split by differing bit.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Lowbit partition.
*/
