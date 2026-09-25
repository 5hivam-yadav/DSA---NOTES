/*
Problem: Power Set Bitmask
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Maths
Statement: Given distinct numbers, return all subsets using bitmasks from 0 to 2^n - 1.
Sample Input: nums = [1,2,3]
Sample Output: 8 subsets incl [] and [1,2,3]
Explanation: Bit i decides membership of nums[i].
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
    vector<vector<int>> subsets(vector<int>& a) {
        int n = a.size();
        vector<vector<int>> r;
        for (int m = 0; m < (1 << n); m++) {
            vector<int> ds;
            for (int i = 0; i < n; i++) if (m >> i & 1) ds.push_back(a[i]);
            r.push_back(ds);
        }
        return r;
    }
};

int main() {
    vector<int> nums = {1, 2, 3};

    Solution sol;
    auto ans = sol.subsets(nums);
    for (int i = 0; i < (int)ans.size(); i++) {
        for (int j = 0; j < (int)ans[i].size(); j++) cout << ans[i][j] << " ";
        cout << endl;
    }
    return 0;
}

/*
Approach:
Mask = subset.
Time Complexity:
O(2^n n)
Space Complexity:
O(1) extra
Key Idea:
Bit i = take.
*/
