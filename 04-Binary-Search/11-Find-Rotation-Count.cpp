/*
Problem: Find Rotation Count
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Search
Statement: Given a rotated sorted array with distinct values, return how many times it was rotated (index of the minimum).
Sample Input: a = [15, 18, 2, 3, 6, 12]
Sample Output: 2
Explanation: Minimum 2 is at index 2, so rotation count is 2.
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

int rotationCount(vector<int>& a) {
    int lo = 0, hi = (int)a.size() - 1;
    while (lo < hi) {
        int m = lo + (hi - lo) / 2;
        if (a[m] > a[hi]) lo = m + 1;
        else hi = m;
    }
    return lo;
}

int main() {
    vector<int> a = {15, 18, 2, 3, 6, 12};

    auto ans = rotationCount(a);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Index of min = K.
Time Complexity:
O(log n)
Space Complexity:
O(1)
Key Idea:
Min index.
*/
