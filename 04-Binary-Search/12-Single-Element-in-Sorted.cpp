/*
Problem: Single Element in Sorted
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Search
Statement: Given a sorted array where every element appears twice except one, find that single element in O(log n).
Sample Input: nums = [1, 1, 2, 3, 3, 4, 4, 8, 8]
Sample Output: 2
Explanation: 2 is the only unpaired value.
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
    int singleNonDuplicate(vector<int>& a) {
        int lo = 0, hi = (int)a.size() - 1;
        while (lo < hi) {
            int m = lo + (hi - lo) / 2;
            if (m % 2 == 1) m--;
            if (a[m] == a[m + 1]) lo = m + 2;
            else hi = m;
        }
        return a[lo];
    }
};

int main() {
    vector<int> nums = {1, 1, 2, 3, 3, 4, 4, 8, 8};

    Solution sol;
    auto ans = sol.singleNonDuplicate(nums);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Pair parity.
Time Complexity:
O(log n)
Space Complexity:
O(1)
Key Idea:
Pairs start even.
*/
