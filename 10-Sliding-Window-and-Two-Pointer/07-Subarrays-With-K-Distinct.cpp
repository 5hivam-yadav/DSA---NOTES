/*
Problem: Subarrays with K Distinct
Platform: LeetCode
Problem Number: -
Difficulty: Easy
Pattern: Sliding Window
Statement: Given an array and k, count subarrays with exactly k distinct values (atMost(K) - atMost(K-1)).
Sample Input: nums = [1,2,1,2,3], k = 2
Sample Output: 7
Explanation: Seven windows contain exactly two distinct values.
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
    int atMost(vector<int>& a, int k) {
        if (k < 0) return 0;
        unordered_map<int, int> f;
        int l = 0, r = 0;
        for (int rr = 0; rr < (int)a.size(); rr++) {
            f[a[rr]]++;
            while ((int)f.size() > k) {
                if (--f[a[l]] == 0) f.erase(a[l]);
                l++;
            }
            r += rr - l + 1;
        }
        return r;
    }
    int subarraysWithKDistinct(vector<int>& a, int k) {
        return atMost(a, k) - atMost(a, k - 1);
    }
};

int main() {
    vector<int> nums = {1, 2, 1, 2, 3};
    int k = 2;

    Solution sol;
    auto ans = sol.atMost(nums, k);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Distinct atMost diff.
Time Complexity:
O(n) avg
Space Complexity:
O(n)
Key Idea:
Freq window.
*/
