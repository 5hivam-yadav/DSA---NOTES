/*
Problem: Buy Sell Stock II
Platform: LeetCode
Problem Number: -
Difficulty: Medium
Pattern: DP - Stocks
Statement: Given prices, return max profit with unlimited transactions (sum
every positive daily difference). Sample Input: prices = [7,1,5,3,6,4] Sample
Output: 7 Explanation: (5-1) + (6-3) = 7.
*/
#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
  public:
    int maxProfit(vector<int> &p) {
        int ans = 0;
        for (size_t i = 1; i < p.size(); i++)
            if (p[i] > p[i - 1])
                ans += p[i] - p[i - 1];
        return ans;
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
Add climbs.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Sum positive diffs.
*/
