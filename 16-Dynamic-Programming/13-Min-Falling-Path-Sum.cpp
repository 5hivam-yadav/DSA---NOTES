/*
Problem: Min Falling Path Sum
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given a square matrix, return the minimum falling path sum moving down, down-left or down-right.
Sample Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
Sample Output: 13
Explanation: Path 1->4->8? best 1+5+7 = 13.
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
    int minFallingPathSum(vector<vector<int>>& a) {
        int n = (int)a.size();
        vector<int> dp = a[0];
        for (int i = 1; i < n; i++) {
            vector<int> nd(n, 0);
            for (int j = 0; j < n; j++) {
                int best = dp[j];
                if (j > 0) best = min(best, dp[j - 1]);
                if (j + 1 < n) best = min(best, dp[j + 1]);
                nd[j] = a[i][j] + best;
            }
            dp.swap(nd);
        }
        return *min_element(dp.begin(), dp.end());
    }
};

int main() {
    vector<vector<int>> matrix = {{2, 1, 3}, {6, 5, 4}, {7, 8, 9}};

    Solution sol;
    auto ans = sol.minFallingPathSum(matrix);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Variable start/end, 3 choices from row above.
Time Complexity:
O(n^2)
Space Complexity:
O(n)
Key Idea:
Guard edges, min of up/up-left/up-right.
*/
