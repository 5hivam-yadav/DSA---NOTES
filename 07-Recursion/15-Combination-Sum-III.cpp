/*
Problem: Combination Sum III
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Backtracking
Statement: Given k and n, return all k-number combos from 1..9 summing to n,
each number used once. Sample Input: k = 3, n = 9 Sample Output:
[[1,2,6],[1,3,5],[2,3,4]] Explanation: Three combos of size 3 sum to 9.
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
    vector<vector<int>> ans;
    vector<int> ds;
    void f(int s, int k, int t) {
        if ((int)ds.size() == k) {
            if (t == 0)
                ans.push_back(ds);
            return;
        }
        for (int i = s; i <= 9; i++) {
            if (i > t)
                break;
            ds.push_back(i);
            f(i + 1, k, t - i);
            ds.pop_back();
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        f(1, k, n);
        return ans;
    }
};

int main() {
    int k = 3;
    int n = 9;

    Solution sol;
    auto ans = sol.combinationSum3(k, n);
    for (int i = 0; i < (int)ans.size(); i++) {
        for (int j = 0; j < (int)ans[i].size(); j++)
            cout << ans[i][j] << " ";
        cout << endl;
    }
    return 0;
}

/*
Approach:
Digits 1..9 once.
Time Complexity:
O(C(9, k))
Space Complexity:
O(k)
Key Idea:
Bounded combo.
*/
