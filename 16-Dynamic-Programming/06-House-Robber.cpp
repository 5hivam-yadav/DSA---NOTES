/*
Problem: House Robber
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP - 1D
Statement: Given house values in a row, return the maximum loot without robbing adjacent houses.
Sample Input: nums = [2,7,9,3,1]
Sample Output: 12
Explanation: Rob 2, 9, 1 for total 12.
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
    int rob(vector<int>& a) {
        int p2 = 0, p1 = 0;
        for (int x : a) {
            int c = max(p1, p2 + x);
            p2 = p1;
            p1 = c;
        }
        return p1;
    }
};

int main() {
    vector<int> nums = {2, 7, 9, 3, 1};

    Solution sol;
    auto ans = sol.rob(nums);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Same as non-adjacent.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Adjacent exclusion.
*/
