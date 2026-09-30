/*
Problem: Trapping Rain Water
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Monotonic Stack
Statement: Given bar heights, return trapped rain water where water at i is
min(maxLeft, maxRight) - h[i]. Sample Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Sample Output: 6
Explanation: Valleys hold 6 units in total.
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
    int trap(vector<int> &h) {
        int l = 0, r = (int)h.size() - 1, lm = 0, rm = 0, ans = 0;
        while (l < r) {
            if (h[l] < h[r]) {
                lm = max(lm, h[l]);
                ans += lm - h[l++];
            } else {
                rm = max(rm, h[r]);
                ans += rm - h[r--];
            }
        }
        return ans;
    }
};

int main() {
    vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

    Solution sol;
    auto ans = sol.trap(height);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Water=min(Lmax, Rmax)-h.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Lower side decides.
*/
