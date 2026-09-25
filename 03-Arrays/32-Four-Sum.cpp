/*
Problem: Four Sum
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Two Pointers
Statement: Given an array and target, return all unique quadruplets summing to target (sort + two pointers).
Sample Input: nums = [1, 0, -1, 0, -2, 2], target = 0
Sample Output: [[-2, -1, 1, 2], [-2, 0, 0, 2], [-1, 0, 0, 1]]
Explanation: Three distinct quadruplets sum to 0.
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
    vector<vector<int>> fourSum(vector<int>& a, int t) {
        sort(a.begin(), a.end());
        vector<vector<int>> r;
        int n = a.size();
        for (int i = 0; i < n; i++) {
            if (i > 0 && a[i] == a[i - 1]) continue;
            for (int j = i + 1; j < n; j++) {
                if (j > i + 1 && a[j] == a[j - 1]) continue;
                int l = j + 1, rr = n - 1;
                while (l < rr) {
                    long long s = 1LL * a[i] + a[j] + a[l] + a[rr];
                    if (s == t) {
                        r.push_back({a[i], a[j], a[l], a[rr]});
                        l++;
                        rr--;
                        while (l < rr && a[l] == a[l - 1]) l++;
                        while (l < rr && a[rr] == a[rr + 1]) rr--;
                    }
                    else if (s < t) l++;
                    else rr--;
                }
            }
        }
        return r;
    }
};

int main() {
    vector<int> nums = {1, 0, -1, 0, -2, 2};
    int target = 0;

    Solution sol;
    auto ans = sol.fourSum(nums, target);
    for (int i = 0; i < (int)ans.size(); i++) {
        for (int j = 0; j < (int)ans[i].size(); j++) cout << ans[i][j] << " ";
        cout << endl;
    }
    return 0;
}

/*
Approach:
Fix i, j + 2ptr.
Time Complexity:
O(n^3)
Space Complexity:
O(1) extra
Key Idea:
long long sum.
*/
