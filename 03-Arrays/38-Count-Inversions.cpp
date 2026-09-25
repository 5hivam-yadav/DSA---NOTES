/*
Problem: Count Inversions
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Arrays
Statement: Given an array, count pairs (i < j) with a[i] > a[j] using merge sort in O(n log n).
Sample Input: a = [2, 4, 1, 3, 5]
Sample Output: 3
Explanation: Inversions are (2,1), (4,1), (4,3).
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

long long mergeC(vector<int>& a, int l, int m, int r) {
    vector<int> t;
    int i = l, j = m + 1;
    long long c = 0;
    while (i <= m && j <= r) {
        if (a[i] <= a[j]) t.push_back(a[i++]);
        else {
            c += (m - i + 1);
            t.push_back(a[j++]);
        }
    }
    while (i <= m) t.push_back(a[i++]);
    while (j <= r) t.push_back(a[j++]);
    copy(t.begin(), t.end(), a.begin() + l);
    return c;
}
long long inv(vector<int>& a, int l, int r) {
    if (l >= r) return 0;
    int m = (l + r) / 2;
    return inv(a, l, m) + inv(a, m + 1, r) + mergeC(a, l, m, r);
}

/*
Approach:
Merge-sort count.
Time Complexity:
O(n log n)
Space Complexity:
O(n)
Key Idea:
Right-smaller jumps count.
*/
