/*
Problem: Binary Subarrays with Sum
Platform: LeetCode
Problem Number: -
Difficulty: Easy
Pattern: Sliding Window
Statement: Given a binary array and goal, count subarrays summing to goal via prefix sums (or atMost(K) - atMost(K-1)).
Sample Input: nums = [1,0,1,0,1], goal = 2
Sample Output: 4
Explanation: Four windows contain exactly two 1s.
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
    int atMost(vector<int>& a, int k) {
        if (k < 0) return 0;
        int l = 0, s = 0, r = 0;
        for (int rr = 0; rr < (int)a.size(); rr++) {
            s += a[rr];
            while (s > k) {
                s -= a[l++];
            }
            r += rr - l + 1;
        }
        return r;
    }
    int numSubarraysWithSum(vector<int>& a, int k) {
        return atMost(a, k) - atMost(a, k - 1);
    }
};

int main() {
    vector<int> nums = {1, 0, 1, 0, 1};
    int goal = 2;

    Solution sol;
    auto ans = sol.atMost(nums, goal);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Exact = atMost diff.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
f(K)-f(K-1).
*/
