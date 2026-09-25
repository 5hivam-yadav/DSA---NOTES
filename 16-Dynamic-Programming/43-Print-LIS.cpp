/*
Problem: Print Longest Increasing Subsequence
Platform: LeetCode
Problem Number: -
Difficulty: Medium
Pattern: DP - LIS
Statement: Given an array, return one longest strictly increasing subsequence (DP lengths + parent backtrack).
Sample Input: nums = [10,9,2,5,3,7,101,18]
Sample Output: [2,3,7,101]
Explanation: One LIS of length 4.
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

vector<int> printLIS(vector<int>& a) {
    int n = a.size();
    vector<int> dp(n, 1), par(n, -1);
    int bi = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
            dp[i] = dp[j] + 1;
            par[i] = j;
        }
        if (dp[i] > dp[bi]) bi = i;
    }
    vector<int> r;
    for (int i = bi; i != -1; i = par[i]) r.push_back(a[i]);
    reverse(r.begin(), r.end());
    return r;
}

int main() {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};

    auto ans = printLIS(nums);
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Parent pointers.
Time Complexity:
O(n^2)
Space Complexity:
O(n)
Key Idea:
Backtrack best end.
*/
