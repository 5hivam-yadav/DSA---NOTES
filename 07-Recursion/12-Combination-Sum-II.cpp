/*
Problem: Combination Sum II
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Backtracking
Statement: Given candidates with duplicates and target, return unique combinations using each element at most once.
Sample Input: candidates = [10,1,2,7,6,1,5], target = 8
Sample Output: [[1,1,6],[1,2,5],[1,7],[2,6]]
Explanation: Four distinct combos sum to 8.
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
        for (int j = i; j < (int)c.size(); j++) {
            if (j > i && c[j] == c[j - 1]) continue;
            if (c[j] > t) break;
            ds.push_back(c[j]);
            f(j + 1, c, t - c[j]);
            ds.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& c, int t) {
        sort(c.begin(), c.end());
        f(0, c, t);
        return ans;
    }
};

int main() {
    vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
    int target = 8;

    Solution sol;
    auto ans = sol.combinationSum2(candidates, target);
    for (int i = 0; i < (int)ans.size(); i++) {
        for (int j = 0; j < (int)ans[i].size(); j++) cout << ans[i][j] << " ";
        cout << endl;
    }
    return 0;
}

/*
Approach:
Once + skip dups.
Time Complexity:
O(2^n)
Space Complexity:
O(n)
Key Idea:
Single-use combo.
*/
