/*
Problem: Two Sum
Platform: LeetCode
Problem Number: -
Difficulty: Easy
Pattern: Two Pointers
Statement: Given an array nums and target, return the indices of the two numbers
adding to target. Exactly one solution exists. Sample Input: nums = [2, 7, 11,
15], target = 9 Sample Output: [0, 1] Explanation: nums[0] + nums[1] = 2 + 7
= 9.
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
    vector<int> twoSum(vector<int> &a, int t) {
        unordered_map<int, int> m;
        for (int i = 0; i < (int)a.size(); i++) {
            int need = t - a[i];
            if (m.count(need))
                return {m[need], i};
            m[a[i]] = i;
        }
        return {};
    }
};

int main() {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    Solution sol;
    auto ans = sol.twoSum(nums, target);
    for (int i = 0; i < (int)ans.size(); i++)
        cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Complement lookup.
Time Complexity:
O(n) avg
Space Complexity:
O(n)
Key Idea:
Hash complements.
*/
