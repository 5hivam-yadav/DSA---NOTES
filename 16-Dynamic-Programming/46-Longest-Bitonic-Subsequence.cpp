/*
Problem: Longest Bitonic Subsequence
Platform: LeetCode
Problem Number: -
Difficulty: Medium
Pattern: DP - LIS
Statement: Given an array, return the length of the longest bitonic subsequence (increasing then decreasing; LIS both sides).
Sample Input: nums = [1,11,2,10,4,5,2,1]
Sample Output: 6
Explanation: [1,2,10,4,2,1] (or [1,11,10,5,2,1]) has length 6.
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

int bitonic(vector<int>& a) {
    int n = a.size();
    vector<int> inc(n, 1), dec(n, 1);
    for (int i = 0; i < n; i++) for (int j = 0; j < i; j++) if (a[j] < a[i]) inc[i] = max(inc[i], inc[j] + 1);
    for (int i = n - 1; i >= 0; i--) for (int j = n - 1; j > i; j--) if (a[j] < a[i]) dec[i] = max(dec[i], dec[j] + 1);
    int b = 0;
    for (int i = 0; i < n; i++) b = max(b, inc[i] + dec[i] - 1);
    return b;
}

int main() {
    vector<int> nums = {1, 11, 2, 10, 4, 5, 2, 1};

    auto ans = bitonic(nums);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Inc + dec peak.
Time Complexity:
O(n^2)
Space Complexity:
O(n)
Key Idea:
Peak both sides.
*/
