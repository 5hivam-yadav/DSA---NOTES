/*
Problem: Reverse Pairs
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Arrays
Statement: Given an array, count pairs (i < j) with a[i] > 2*a[j] using merge sort in O(n log n).
Sample Input: nums = [1, 3, 2, 3, 1]
Sample Output: 2
Explanation: Pairs are (3,1) at (1,4) and (3,1) at (3,4).
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
    long long c = 0;
    void ms(vector<int>& a, int l, int r) {
        if (l >= r) return;
        int m = (l + r) / 2;
        ms(a, l, m);
        ms(a, m + 1, r);
        int j = m + 1;
        for (int i = l; i <= m; i++) {
            while (j <= r && 1LL * a[i] > 2LL * a[j]) j++;
            c += (j - m - 1);
        }
        inplace_merge(a.begin() + l, a.begin() + m + 1, a.begin() + r + 1);
    }
    int reversePairs(vector<int>& a) {
        ms(a, 0, (int)a.size() - 1);
        return (int)c;
    }
};

/*
Approach:
Count before merge.
Time Complexity:
O(n log n)
Space Complexity:
O(n)
Key Idea:
Overflow-safe 2*a[j].
*/
