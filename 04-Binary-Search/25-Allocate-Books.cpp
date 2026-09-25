/*
Problem: Allocate Books
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search on Answer
Statement: Given book pages and k students (contiguous allotment), minimize the maximum pages per student (binary search).
Sample Input: pages = [12,34,67,90], k = 2
Sample Output: 113
Explanation: Split [12,34,67] and [90] gives max 113.
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

bool ok(vector<int>& p, int s, int mx) {
    int c = 1;
    long long cur = 0;
    for (int x : p) {
        if (x > mx) return false;
        if (cur + x > mx) {
            c++;
            cur = 0;
        }
        cur += x;
    }
    return c <= s;
}
int allocate(vector<int>& p, int s) {
    if (s > (int)p.size()) return -1;
    int lo = *max_element(p.begin(), p.end()), hi = accumulate(p.begin(), p.end(), 0);
    while (lo <= hi) {
        int m = lo + (hi - lo) / 2;
        if (ok(p, s, m)) hi = m - 1;
        else lo = m + 1;
    }
    return lo;
}

int main() {
    vector<int> pages = {12, 34, 67, 90};
    int k = 2;

    auto ans = allocate(pages, k);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Students feasibility.
Time Complexity:
O(n log Sum)
Space Complexity:
O(1)
Key Idea:
Min-max pages.
*/
