/*
Problem: Buy Sell Stock I
Platform: LeetCode
Problem Number: -
Difficulty: Medium
Pattern: DP - Stocks
Statement: Given prices by day, return max profit from one buy then later sell; 0 if no profit possible.
Sample Input: prices = [7, 1, 5, 3, 6, 4]
Sample Output: 5
Explanation: Buy at 1, sell at 6 for profit 5.
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
        int mn = INT_MAX, b = 0;
        for (int x : p) {
            mn = min(mn, x);
            b = max(b, x - mn);
        }
        return b;
    }
};

int main() {
    vector<int> prices = {7, 1, 5, 3, 6, 4};

    Solution sol;
    auto ans = sol.maxProfit(prices);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Min so far.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Buy lowest before.
*/
