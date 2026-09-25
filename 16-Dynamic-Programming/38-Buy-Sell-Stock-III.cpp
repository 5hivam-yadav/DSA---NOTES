/*
Problem: Buy Sell Stock III
Platform: LeetCode
Problem Number: -
Difficulty: Medium
Pattern: DP - Stocks
Statement: Given prices, return max profit with at most two transactions (two-pass DP).
Sample Input: prices = [3,3,5,0,0,3,1,4]
Sample Output: 6
Explanation: Buy 0 sell 3 (3) + buy 1 sell 4 (3) = 6.
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
        int b1 = INT_MAX, b2 = INT_MAX, s1 = 0, s2 = 0;
        for (int x : p) {
            b1 = min(b1, x);
            s1 = max(s1, x - b1);
            b2 = min(b2, x - s1);
            s2 = max(s2, x - b2);
        }
        return s2;
    }
};

int main() {
    vector<int> prices = {3, 3, 5, 0, 0, 3, 1, 4};

    Solution sol;
    auto ans = sol.maxProfit(prices);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Four states.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Two buys/sells.
*/
