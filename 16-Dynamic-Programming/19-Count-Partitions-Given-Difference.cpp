/*
Problem: Count Partitions Given Difference
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Dynamic Programming
Statement: Given an array and D, count partitions with subset difference D (subset sum (total-D)/2; zero if parity mismatches).
Sample Input: a = [5,2,6,4], D = 3
Sample Output: 1
Explanation: Subset [5,2]=7 vs [6,4]=10 differs by 3.
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

const int MOD = 1000000007;

int countPartitions(vector<int>& a, int D) {
    int sum = accumulate(a.begin(), a.end(), 0);
    if ((sum - D) < 0 || (sum - D) % 2) return 0;
    int K = (sum - D) / 2;
    vector<int> dp(K + 1, 0);
    dp[0] = 1;
    for (int x : a) {
        for (int s = K; s >= x; s--) dp[s] = (dp[s] + dp[s - x]) % MOD;
        if (x == 0) dp[0] = (dp[0] * 2) % MOD;
    }
    return dp[K];
}

int main() {
    vector<int> a = {5, 2, 6, 4};
    int D = 3;

    auto ans = countPartitions(a, D);
    cout << ans << endl;
    return 0;
}

/*
Approach:
s1-s2=D, s1+s2=sum => s2=(sum-D)/2 subset count.
Time Complexity:
O(n*sum)
Space Complexity:
O(sum)
Key Idea:
Parity check first.
*/
