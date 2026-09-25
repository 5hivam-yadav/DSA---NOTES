/*
Problem: Buy Sell Stock Cooldown
Platform: LeetCode
Problem Number: -
Difficulty: Medium
Pattern: DP - Stocks
Statement: Given prices with a one-day cooldown after selling, return max profit (hold/sold/rest states).
Sample Input: prices = [1,2,3,0,2]
Sample Output: 3
Explanation: Buy 1 sell 2? best is buy 1 sell 3 then buy 0 sell 2 = 3.
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
    int maxProfit(vector<int>& p) {
        int hold = INT_MIN, sold = 0, rest = 0;
        for (int x : p) {
            int ph = hold, ps = sold, pr = rest;
            hold = max(ph, pr - x);
            sold = ph + x;
            rest = max(pr, ps);
        }
        return max(sold, rest);
    }
};

int main() {
    vector<int> prices = {1, 2, 3, 0, 2};

    Solution sol;
    auto ans = sol.maxProfit(prices);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Hold/sold/rest.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Cooldown = rest only.
*/
