/*
Problem: Minimum Coins
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP - Coin Change
Statement: Given coin denominations and amount, return the minimum coins to make
amount, or -1 if impossible (unbounded DP). Sample Input: coins = [1,2,5],
amount = 11 Sample Output: 3 Explanation: 5 + 5 + 1 = 11 with 3 coins.
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

int minCoins(int v) {
    vector<int> d = {1, 2, 5, 10, 20, 50, 100, 500, 1000};
    int c = 0;
    for (int i = (int)d.size() - 1; i >= 0; i--) {
        c += v / d[i];
        v %= d[i];
    }
    return c;
}
// Greedy fails on non-canonical sets; use DP.

int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 11;

    auto ans = minCoins(amount);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Largest-first.
Time Complexity:
O(1)
Space Complexity:
O(1)
Key Idea:
Canonical denominations.
*/
