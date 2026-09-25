/*
Problem: Aggressive Cows
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search on Answer
Statement: Given stall positions and c cows, maximize the minimum distance between cows (binary search on answer).
Sample Input: stalls = [1, 2, 4, 8, 9], c = 3
Sample Output: 3
Explanation: Placing at 1, 4, 8 gives minimum gap 3.
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

bool ok(vector<int>& s, int k, int d) {
    int c = 1, last = s[0];
    for (size_t i = 1; i < s.size(); i++) if (s[i] - last >= d) {
        c++;
        last = s[i];
    }
    return c >= k;
}
int aggressive(vector<int>& s, int k) {
    sort(s.begin(), s.end());
    int lo = 1, hi = s.back() - s.front();
    while (lo <= hi) {
        int m = lo + (hi - lo) / 2;
        if (ok(s, k, m)) lo = m + 1;
        else hi = m - 1;
    }
    return hi;
}

int main() {
    vector<int> stalls = {1, 2, 4, 8, 9};
    int c = 3;

    auto ans = aggressive(stalls, c);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Max-min distance.
Time Complexity:
O(n log n)
Space Complexity:
O(1)
Key Idea:
Greedy place + BS.
*/
