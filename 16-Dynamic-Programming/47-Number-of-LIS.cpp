/*
Problem: Number of Longest Increasing Subsequence
Platform: LeetCode
Problem Number: -
Difficulty: Medium
Pattern: DP - LIS
Statement: Given an array, count how many longest increasing subsequences exist (length DP + count DP).
Sample Input: nums = [1,3,5,4,7]
Sample Output: 2
Explanation: LIS length 4 via [1,3,4,7] and [1,3,5,7].
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
    int findNumberOfLIS(vector<int>& a) {
        int n = a.size();
        vector<int> len(n, 1), cnt(n, 1);
        int b = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) if (a[j] < a[i]) {
                if (len[j] + 1 > len[i]) {
                    len[i] = len[j] + 1;
                    cnt[i] = cnt[j];
                }
                else if (len[j] + 1 == len[i]) cnt[i] += cnt[j];
            }
            b = max(b, len[i]);
        }
        int ans = 0;
        for (int i = 0; i < n; i++) if (len[i] == b) ans += cnt[i];
        return ans;
    }
};

int main() {
    vector<int> nums = {1, 3, 5, 4, 7};

    Solution sol;
    auto ans = sol.findNumberOfLIS(nums);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Len + count.
Time Complexity:
O(n^2)
Space Complexity:
O(n)
Key Idea:
Merge equal-length counts.
*/
