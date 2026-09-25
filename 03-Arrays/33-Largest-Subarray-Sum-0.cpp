/*
Problem: Largest Subarray Sum 0
Platform: LeetCode
Problem Number: -
Difficulty: Medium
Pattern: DP - 1D
Statement: Given an array, return the length of the longest subarray summing to 0 (prefix sums + first-occurrence map).
Sample Input: a = [15, -2, 2, -8, 1, 7, 10, 23]
Sample Output: 5
Explanation: Subarray [-2, 2, -8, 1, 7] sums to 0 with length 5.
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

int maxLen0(vector<int>& a) {
    unordered_map<long long, int> f;
    f[0] = -1;
    long long s = 0;
    int b = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        s += a[i];
        if (f.count(s)) b = max(b, i - f[s]);
        else f[s] = i;
    }
    return b;
}

int main() {
    vector<int> a = {15, -2, 2, -8, 1, 7, 10, 23};

    auto ans = maxLen0(a);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Repeat prefix => zero-sum.
Time Complexity:
O(n) avg
Space Complexity:
O(n)
Key Idea:
First occurrence longest.
*/
