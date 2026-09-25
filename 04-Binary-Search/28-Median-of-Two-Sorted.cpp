/*
Problem: Median of Two Sorted
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Binary Search
Statement: Given two sorted arrays, return the median of the combined array in O(log(min(m, n))).
Sample Input: a = [1, 3], b = [2]
Sample Output: 2.0
Explanation: Merged [1, 2, 3] has median 2.
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
    double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
        if (a.size() > b.size()) return findMedianSortedArrays(b, a);
        int n = a.size(), m = b.size(), lo = 0, hi = n;
        while (lo <= hi) {
            int i = (lo + hi) / 2, j = (n + m + 1) / 2 - i;
            int aL = (i == 0 ? INT_MIN : a[i - 1]), aR = (i == n ? INT_MAX : a[i]);
            int bL = (j == 0 ? INT_MIN : b[j - 1]), bR = (j == m ? INT_MAX : b[j]);
            if (aL <= bR && bL <= aR) {
                if ((n + m) % 2) return max(aL, bL);
                return (max(aL, bL) + min(aR, bR)) / 2.0;
            }
            else if (aL > bR) hi = i - 1;
            else lo = i + 1;
        }
        return 0;
    }
};

int main() {
    vector<int> a = {1, 3};
    vector<int> b = {2};

    Solution sol;
    auto ans = sol.findMedianSortedArrays(a, b);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Partition halves.
Time Complexity:
O(log min(n, m))
Space Complexity:
O(1)
Key Idea:
Left max <= right min.
*/
