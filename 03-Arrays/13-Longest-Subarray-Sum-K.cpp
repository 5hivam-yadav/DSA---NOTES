/*
Problem: Longest Subarray Sum K
Platform: LeetCode
Problem Number: -
Difficulty: Medium
Pattern: Sliding Window
Statement: Given an array and k, return the length of the longest subarray summing to k (prefix sums + hashmap).
Sample Input: a = [1, 2, 1, 2, 3], k = 5
Sample Output: 3
Explanation: Subarray [2, 1, 2] sums to 5 with length 3.
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

int longestK(vector<int>& a, int k) {
    unordered_map<long long, int> f;
    long long s = 0;
    int b = 0;
    f[0] = -1;
    for (int i = 0; i < (int)a.size(); i++) {
        s += a[i];
        if (f.count(s - k)) b = max(b, i - f[s - k]);
        if (!f.count(s)) f[s] = i;
    }
    return b;
}

int main() {
    vector<int> a = {1, 2, 1, 2, 3};
    int k = 5;

    auto ans = longestK(a, k);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Prefix + first index.
Time Complexity:
O(n) avg
Space Complexity:
O(n)
Key Idea:
Earliest prefix longest.
*/
