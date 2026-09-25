/*
Problem: Jump Game I
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Greedy
Statement: Given jump lengths, return true if the last index is reachable (track farthest reachable).
Sample Input: nums = [2,3,1,1,4]
Sample Output: true
Explanation: Jumps 2 -> 3 -> 4 reach the end.
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
    bool canJump(vector<int>& a) {
        int r = 0;
        for (int i = 0; i < (int)a.size(); i++) {
            if (i > r) return false;
            r = max(r, i + a[i]);
        }
        return true;
    }
};

int main() {
    vector<int> nums = {2, 3, 1, 1, 4};

    Solution sol;
    auto ans = sol.canJump(nums);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
Track farthest.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Reachable frontier.
*/
