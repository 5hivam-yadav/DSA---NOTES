/*
Problem: Subsets II
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Recursion
Statement: Given numbers that may repeat, return all unique subsets (sort + skip duplicate branches).
Sample Input: nums = [1,2,2]
Sample Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
Explanation: Six distinct subsets exist.
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
    void f(int i, vector<int>& a) {
        ans.push_back(ds);
        for (int j = i; j < (int)a.size(); j++) {
            if (j > i && a[j] == a[j - 1]) continue;
            ds.push_back(a[j]);
            f(j + 1, a);
            ds.pop_back();
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& a) {
        sort(a.begin(), a.end());
        f(0, a);
        return ans;
    }
};

int main() {
    vector<int> nums = {1, 2, 2};

    Solution sol;
    auto ans = sol.subsetsWithDup(nums);
    for (int i = 0; i < (int)ans.size(); i++) {
        for (int j = 0; j < (int)ans[i].size(); j++) cout << ans[i][j] << " ";
        cout << endl;
    }
    return 0;
}

/*
Approach:
Sort + skip dup starts.
Time Complexity:
O(2^n n)
Space Complexity:
O(n)
Key Idea:
Dup-aware loop.
*/
