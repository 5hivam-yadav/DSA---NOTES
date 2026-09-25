/*
Problem: Permutations II
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Recursion
Statement: Given numbers that may repeat, return all unique permutations.
Sample Input: nums = [1,1,2]
Sample Output: [[1,1,2],[1,2,1],[2,1,1]]
Explanation: Three distinct orderings exist.
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
    vector<int> used;
    void f(vector<int>& a) {
        if (ds.size() == a.size()) {
            ans.push_back(ds);
            return;
        }
        for (size_t i = 0; i < a.size(); i++) {
            if (used[i]) continue;
            if (i > 0 && a[i] == a[i-1] && !used[i-1]) continue;
            used[i] = 1;
            ds.push_back(a[i]);
            f(a);
            ds.pop_back();
            used[i] = 0;
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& a) {
        sort(a.begin(), a.end());
        used.assign(a.size(), 0);
        f(a);
        return ans;
    }
};

int main() {
    vector<int> nums = {1, 1, 2};
    Solution sol;
    auto ans = sol.permuteUnique(nums);
    cout << "[";
    for (size_t i = 0; i < ans.size(); i++) {
        cout << "[";
        for (size_t j = 0; j < ans[i].size(); j++) cout << ans[i][j] << (j + 1 < ans[i].size() ? "," : "");
        cout << "]" << (i + 1 < ans.size() ? "," : "");
    }
    cout << "]" << endl;
    return 0;
}

/*
Approach:
Sort + skip used-dup.
Time Complexity:
O(n! n)
Space Complexity:
O(n)
Key Idea:
Dup-aware used array.
*/
