/*
Problem: Painters Partition
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search on Answer
Statement: Given board lengths and k painters (contiguous), minimize time = max load (binary search on the answer).
Sample Input: boards = [10,20,30,40], k = 2
Sample Output: 60
Explanation: Split [10,20,30] and [40] gives max 60.
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

bool ok2(vector<int>& b, int k, long long mx) {
    int c = 1;
    long long cur = 0;
    for (int x : b) {
        if (x > mx) return false;
        if (cur + x > mx) {
            c++;
            cur = 0;
        }
        cur += x;
    }
    return c <= k;
}
long long painters(vector<int>& b, int k) {
    long long lo = *max_element(b.begin(), b.end()), hi = accumulate(b.begin(), b.end(), 0LL);
    while (lo <= hi) {
        long long m = lo + (hi - lo) / 2;
        if (ok2(b, k, m)) hi = m - 1;
        else lo = m + 1;
    }
    return lo;
}

int main() {
    vector<int> boards = {10, 20, 30, 40};
    int k = 2;

    auto ans = painters(boards, k);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Same as allocate.
Time Complexity:
O(n log Sum)
Space Complexity:
O(1)
Key Idea:
Contiguous partition.
*/
