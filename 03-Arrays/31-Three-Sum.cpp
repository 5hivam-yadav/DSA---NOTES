/*
Problem: Three Sum
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Two Pointers
Statement: Given an array, return all unique triplets summing to zero (sort + two pointers, skip duplicates).
Sample Input: nums = [-1, 0, 1, 2, -1, -4]
Sample Output: [[-1, -1, 2], [-1, 0, 1]]
Explanation: These are the only distinct zero-sum triplets.
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
    vector<vector<int>> threeSum(vector<int>& a) {
        sort(a.begin(), a.end());
        vector<vector<int>> r;
        int n = a.size();
        for (int i = 0; i < n; i++) {
            if (i > 0 && a[i] == a[i - 1]) continue;
            int l = i + 1, rr = n - 1;
            while (l < rr) {
                int s = a[i] + a[l] + a[rr];
                if (s == 0) {
                    r.push_back({a[i], a[l], a[rr]});
                    l++;
                    rr--;
                    while (l < rr && a[l] == a[l - 1]) l++;
                    while (l < rr && a[rr] == a[rr + 1]) rr--;
                }
                else if (s < 0) l++;
                else rr--;
            }
        }
        return r;
    }
};

int main() {
    vector<int> nums = {-1, 0, 1, 2, -1, -4};

    Solution sol;
    auto ans = sol.threeSum(nums);
    for (int i = 0; i < (int)ans.size(); i++) {
        for (int j = 0; j < (int)ans[i].size(); j++) cout << ans[i][j] << " ";
        cout << endl;
    }
    return 0;
}

/*
Approach:
Fix i, 2-sum sorted.
Time Complexity:
O(n^2)
Space Complexity:
O(1) extra
Key Idea:
Skip dups.
*/
