/*
Problem: Floor and Ceil
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search
Statement: Given a sorted array and x, return the floor (largest value <= x) and ceil (smallest value >= x).
Sample Input: a = [3, 4, 7, 8, 10], x = 5
Sample Output: (4, 7)
Explanation: 4 is the best below 5, 7 the best above.
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

pair<int, int> floorCeil(vector<int>& a, int x) {
    int fl = -1, ce = -1;
    int lo = 0, hi = (int)a.size() - 1;
    while (lo <= hi) {
        int m = lo + (hi - lo) / 2;
        if (a[m] == x) return { x, x};
        else if (a[m] < x) {
            fl = a[m];
            lo = m + 1;
        }
        else {
            ce = a[m];
            hi = m - 1;
        }
    }
    return { fl, ce};
}

int main() {
    vector<int> a = {3, 4, 7, 8, 10};
    int x = 5;

    auto ans = floorCeil(a, x);
    cout << ans.first << " " << ans.second << endl;
    return 0;
}

/*
Approach:
Track best both sides.
Time Complexity:
O(log n)
Space Complexity:
O(1)
Key Idea:
BS with candidates.
*/
