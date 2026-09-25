/*
Problem: Longest Increasing Subsequence
Platform: LeetCode
Problem Number: -
Difficulty: Medium
Pattern: DP - LIS
Statement: Given an array, return the length of the longest strictly increasing subsequence.
Sample Input: nums = [10,9,2,5,3,7,101,18]
Sample Output: 4
Explanation: [2,3,7,101] is one longest subsequence.
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
    int lengthOfLIS(vector<int>& a) {
        vector<int> d;
        for (int x : a) {
            auto it = lower_bound(d.begin(), d.end(), x);
            if (it == d.end()) d.push_back(x);
            else *it = x;
        }
        return d.size();
    }
};
  // O(n^2) DP: dp[i]=1+max dp[j].

int main() {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};

    Solution sol;
    auto ans = sol.lengthOfLIS(nums);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Patience piles.
Time Complexity:
O(n log n)
Space Complexity:
O(n)
Key Idea:
Tails array.
*/
