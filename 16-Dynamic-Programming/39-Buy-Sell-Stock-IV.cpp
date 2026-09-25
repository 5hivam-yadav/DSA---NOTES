/*
Problem: Buy Sell Stock IV
Platform: LeetCode
Problem Number: -
Difficulty: Medium
Pattern: DP - Stocks
Statement: Given k and prices, return max profit with at most k transactions (DP over transactions).
Sample Input: k = 2, prices = [2,4,1]
Sample Output: 2
Explanation: One buy at 2 sell at 4 gives 2.
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
    int maxProfit(int k, vector<int>& p) {
        int n = p.size();
        if (k >= n / 2) {
            int a = 0;
            for (int i = 1; i < n; i++) if (p[i] > p[i-1]) a += p[i] - p[i-1];
            return a;
        }
        vector<int> buy(k + 1, INT_MAX), sell(k + 1, 0);
        for (int x : p) for (int t = 1; t <= k; t++) {
            buy[t] = min(buy[t], x - sell[t-1]);
            sell[t] = max(sell[t], x - buy[t]);
        }
        return sell[k];
    }
};

int main() {
    int k = 2;
    vector<int> prices = {2, 4, 1};

    Solution sol;
    auto ans = sol.maxProfit(k, prices);
    cout << ans << endl;
    return 0;
}

/*
Approach:
K buy/sell pairs.
Time Complexity:
O(nk)
Space Complexity:
O(k)
Key Idea:
Unlimited shortcut.
*/
