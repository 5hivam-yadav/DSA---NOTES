/*
Problem: Combination Sum I
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Backtracking
Statement: Given candidates and target, return all combinations (reuse allowed) summing to target.
Sample Input: candidates = [2,3,6,7], target = 7
Sample Output: [[2,2,3],[7]]
Explanation: 2+2+3 and 7 both hit 7.
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
    vector<vector<int>> ans;
    vector<int> ds;
    void f(int i, vector<int>& c, int t) {
        if (t == 0) {
            ans.push_back(ds);
            return;
        }
        if (i == (int)c.size() || t < 0) return;
        ds.push_back(c[i]);
        f(i, c, t - c[i]);
        ds.pop_back();
        f(i + 1, c, t);
    }
    vector<vector<int>> combinationSum(vector<int>& c, int t) {
        f(0, c, t);
        return ans;
    }
};

int main() {
    vector<int> candidates = {2, 3, 6, 7};
    int target = 7;

    Solution sol;
    auto ans = sol.combinationSum(candidates, target);
    for (int i = 0; i < (int)ans.size(); i++) {
        for (int j = 0; j < (int)ans[i].size(); j++) cout << ans[i][j] << " ";
        cout << endl;
    }
    return 0;
}

/*
Approach:
Pick same or skip.
Time Complexity:
O(2^t)
Space Complexity:
O(t)
Key Idea:
Unlimited reuse.
*/
