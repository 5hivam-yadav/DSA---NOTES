/*
Problem: Implement Lower Bound
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Search
Statement: Given a sorted array and x, return the first index with value >= x (std::lower_bound).
Sample Input: a = [1, 2, 2, 3, 5], x = 2
Sample Output: 1
Explanation: Index 1 is the first value >= 2.
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

int lowerBound(vector<int>& a, int x) {
    int lo = 0, hi = (int)a.size();
    while (lo < hi) {
        int m = lo + (hi - lo) / 2;
        if (a[m] < x) lo = m + 1;
        else hi = m;
    }
    return lo;
}

int main() {
    vector<int> a = {1, 2, 2, 3, 5};
    int x = 2;

    auto ans = lowerBound(a, x);
    cout << ans << endl;
    return 0;
}

/*
Approach:
First >= x.
Time Complexity:
O(log n)
Space Complexity:
O(1)
Key Idea:
lo=first true.
*/
