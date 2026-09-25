/*
Problem: Kth Element of Two Sorted
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Search
Statement: Given two sorted arrays a and b and an integer k, return the k-th smallest element of their union in O(log min(n, m)).
Sample Input: a = [2,3,6,7,9], b = [1,4,8,10], k = 5
Sample Output: 6
Explanation: Merged order 1,2,3,4,6,... puts 6 at position 5.
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

int kthEl(vector<int>& a, vector<int>& b, int k) {
    if (a.size() > b.size()) return kthEl(b, a, k);
    int n = a.size(), m = b.size();
    int lo = max(0, k - m), hi = min(k, n);
    while (lo <= hi) {
        int i = (lo + hi) / 2, j = k - i;
        int aL = (i == 0 ? INT_MIN : a[i - 1]), aR = (i == n ? INT_MAX : a[i]);
        int bL = (j == 0 ? INT_MIN : b[j - 1]), bR = (j == m ? INT_MAX : b[j]);
        if (aL <= bR && bL <= aR) return max(aL, bL);
        else if (aL > bR) hi = i - 1;
        else lo = i + 1;
    }
    return -1;
}

int main() {
    vector<int> a = {2, 3, 6, 7, 9};
    vector<int> b = {1, 4, 8, 10};
    int k = 5;

    auto ans = kthEl(a, b, k);
    cout << ans << endl;
    return 0;
}

/*
Approach:
k-partition.
Time Complexity:
O(log min(n, m))
Space Complexity:
O(1)
Key Idea:
Median generalizes.
*/
