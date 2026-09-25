/*
Problem: Nth Root
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Search
Statement: Given n and m, return floor of the n-th root of m using binary search on the answer.
Sample Input: n = 3, m = 27
Sample Output: 3
Explanation: 3^3 = 27 exactly.
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

long long pw(long long b, int e, long long lim) {
    long long r = 1;
    while (e--) {
        if (r > lim / b) return lim + 1;
        r *= b;
    }
    return r;
}
int nthRoot(int n, int m) {
    int lo = 1, hi = m;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        long long v = pw(mid, n, m);
        if (v == m) return mid;
        else if (v < m) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

int main() {
    int n = 3;
    int m = 27;

    auto ans = nthRoot(n, m);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Power with overflow cap.
Time Complexity:
O(log m * n)
Space Complexity:
O(1)
Key Idea:
Overflow-safe power.
*/
