/*
Problem: Count Nice Subarrays
Platform: LeetCode
Problem Number: -
Difficulty: Easy
Pattern: Sliding Window
Statement: Given an array and k, count subarrays with exactly k odd numbers (prefix counts on odd parity).
Sample Input: nums = [1,1,2,1,1], k = 3
Sample Output: 2
Explanation: Two windows hold exactly three odds.
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
        int l = 0, o = 0, r = 0;
        for (int rr = 0; rr < (int)a.size(); rr++) {
            o += a[rr] % 2;
            while (o > k) {
                o -= a[l++] % 2;
            }
            r += rr - l + 1;
        }
        return r;
    }
    int numberOfSubarrays(vector<int>& a, int k) {
        return atMost(a, k) - atMost(a, k - 1);
    }
};

int main() {
    vector<int> nums = {1, 1, 2, 1, 1};
    int k = 3;

    Solution sol;
    auto ans = sol.atMost(nums, k);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Odds as 0/1.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Same trick on parity.
*/
