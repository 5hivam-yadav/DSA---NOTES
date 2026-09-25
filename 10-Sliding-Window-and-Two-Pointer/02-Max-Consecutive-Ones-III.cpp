/*
Problem: Max Consecutive Ones III
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Sliding Window
Statement: Given a binary array and k, return the maximum number of consecutive 1s obtainable by flipping at most k zeros (sliding window).
Sample Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
Sample Output: 6
Explanation: Flipping the middle two zeros joins 1,1,1,1,1,1 into six 1s.
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
    int longestOnes(vector<int>& a, int k) {
        int l = 0, z = 0, b = 0;
        for (int r = 0; r < (int)a.size(); r++) {
            if (a[r] == 0) z++;
            while (z > k) {
                if (a[l++] == 0) z--;
            }
            b = max(b, r - l + 1);
        }
        return b;
    }
};

int main() {
    vector<int> nums = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
    int k = 2;

    Solution sol;
    auto ans = sol.longestOnes(nums, k);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Zeros <= k window.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Zero budget.
*/
