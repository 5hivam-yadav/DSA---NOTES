/*
Problem: Triangle
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP on Grids
Statement: Given a triangle array, return the minimum top-to-bottom path sum moving to adjacent lower entries.
Sample Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Sample Output: 11
Explanation: Path 2->3->5->1 sums to 11.
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
    int minimumTotal(vector<vector<int>>& t) {
        int n = (int)t.size();
        vector<int> dp = t.back();
        for (int i = n - 2; i >= 0; i--) {
            for (int j = 0; j <= i; j++) {
                dp[j] = t[i][j] + min(dp[j], dp[j + 1]);
            }
        }
        return dp[0];
    }
};

int main() {
    vector<vector<int>> triangle = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};

    Solution sol;
    auto ans = sol.minimumTotal(triangle);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Bottom-up: best of two children below.
Time Complexity:
O(n^2)
Space Complexity:
O(n)
Key Idea:
Fixed bottom row, fold upwards.
*/
