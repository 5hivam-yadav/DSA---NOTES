/*
Problem: Median in Rowwise Sorted
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Binary Search
Statement: Given a row-wise sorted matrix, return its median using value-range binary search with per-row upper bounds.
Sample Input: mat = [[1,3,5],[2,6,9],[3,6,9]]
Sample Output: 5
Explanation: Sorted values are 1,2,3,3,5,6,6,9,9; median is 5.
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

int medianRow(vector<vector<int>>& m) {
    int R = m.size(), C = m[0].size();
    int lo = INT_MAX, hi = INT_MIN;
    for (auto& r : m) {
        lo = min(lo, r[0]);
        hi = max(hi, r.back());
    }
    int want = (R * C + 1) / 2;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2, cnt = 0;
        for (auto& r : m) cnt += upper_bound(r.begin(), r.end(), mid) - r.begin();
        if (cnt < want) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

int main() {
    vector<vector<int>> mat = {{1, 3, 5}, {2, 6, 9}, {3, 6, 9}};

    auto ans = medianRow(mat);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Count <= mid per row.
Time Complexity:
O(R log C log range)
Space Complexity:
O(1)
Key Idea:
Value BS with counts.
*/
