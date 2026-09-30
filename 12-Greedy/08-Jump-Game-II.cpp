/*
Problem: Jump Game II
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Greedy
Statement: Given jump lengths (reachable guaranteed), return the minimum number
of jumps via greedy ranges. Sample Input: nums = [2,3,1,1,4] Sample Output: 2
Explanation: Jump 2 -> 3 -> end in 2 jumps.
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
    int jump(vector<int> &a) {
        int j = 0, cur = 0, far = 0;
        for (int i = 0; i < (int)a.size() - 1; i++) {
            far = max(far, i + a[i]);
            if (i == cur) {
                j++;
                cur = far;
            }
        }
        return j;
    }
};

int main() {
    vector<int> nums = {2, 3, 1, 1, 4};

    Solution sol;
    auto ans = sol.jump(nums);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Layer windows.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
BFS layers.
*/
