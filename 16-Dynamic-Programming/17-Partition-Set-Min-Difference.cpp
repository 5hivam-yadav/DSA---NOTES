/*
Problem: Partition Set Min Difference
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP - Knapsack
Statement: Given an array, split it into two subsets minimizing the absolute sum difference (subset-sum near total/2).
Sample Input: a = [1,6,11,5]
Sample Output: 1
Explanation: Subsets [1,5,6]=12 and [11]=11 differ by 1.
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

int minDifference(vector<int>& a) {
    int sum = accumulate(a.begin(), a.end(), 0);
    vector<char> dp(sum + 1, 0);
    dp[0] = 1;
    for (int x : a)
    for (int s = sum; s >= x; s--) dp[s] = dp[s] || dp[s - x];
    int ans = sum;
    for (int s = 0; s <= sum; s++)
    if (dp[s]) ans = min(ans, abs(sum - 2 * s));
    return ans;
}

int main() {
    vector<int> a = {1, 6, 11, 5};

    auto ans = minDifference(a);
    cout << ans << endl;
    return 0;
}

/*
Approach:
All reachable sums, closest to sum/2 wins.
Time Complexity:
O(n*sum)
Space Complexity:
O(sum)
Key Idea:
|s1-s2| = |sum-2*s1|.
*/
