/*
Problem: Count Occurrences
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Search
Statement: Given a sorted array and x, return how many times x occurs (upper_bound - lower_bound).
Sample Input: a = [5, 7, 7, 8, 8, 10], x = 8
Sample Output: 2
Explanation: 8 spans indices 3 to 4, so count is 2.
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

int countOcc(vector<int>& a, int x) {
    auto l = lower_bound(a.begin(), a.end(), x);
    auto r = upper_bound(a.begin(), a.end(), x);
    if (l == a.end() || *l != x) return 0;
    return (int)(r - l);
}

int main() {
    vector<int> a = {5, 7, 7, 8, 8, 10};
    int x = 8;

    auto ans = countOcc(a, x);
    cout << ans << endl;
    return 0;
}

/*
Approach:
upper - lower.
Time Complexity:
O(log n)
Space Complexity:
O(1)
Key Idea:
Range length.
*/
