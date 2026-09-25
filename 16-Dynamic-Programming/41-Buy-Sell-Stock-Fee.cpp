/*
Problem: Buy Sell Stock Fee
Platform: LeetCode
Problem Number: -
Difficulty: Medium
Pattern: DP - Stocks
Statement: Given prices and per-trade fee, return max profit subtracting the fee on each sell.
Sample Input: prices = [1,3,2,8,4,9], fee = 2
Sample Output: 8
Explanation: (8-1-2) + (9-4-2) = 8.
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
    int maxProfit(vector<int>& p, int fee) {
        int hold = INT_MIN, cash = 0;
        for (int x : p) {
            int ph = hold;
            hold = max(hold, cash - x);
            cash = max(cash, ph + x - fee);
        }
        return cash;
    }
};

int main() {
    vector<int> prices = {1, 3, 2, 8, 4, 9};
    int fee = 2;

    Solution sol;
    auto ans = sol.maxProfit(prices, fee);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Fee on sell.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Hold/cash states.
*/
