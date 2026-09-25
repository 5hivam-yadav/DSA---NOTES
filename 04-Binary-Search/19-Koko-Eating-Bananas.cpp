/*
Problem: Koko Eating Bananas
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search on Answer
Statement: Given piles and h hours, find the minimum eating speed k so all bananas finish in h hours (binary search on answer).
Sample Input: piles = [3, 6, 7, 11], h = 8
Sample Output: 4
Explanation: Speed 4 finishes in exactly 8 hours.
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
    int minEatingSpeed(vector<int>& p, int h) {
        int lo = 1, hi = 1e9;
        while (lo < hi) {
            int m = lo + (hi - lo) / 2;
            long long t = 0;
            for (int x : p) t += (x + m - 1) / m;
            if (t <= h) hi = m;
            else lo = m + 1;
        }
        return lo;
    }
};

int main() {
    vector<int> piles = {3, 6, 7, 11};
    int h = 8;

    Solution sol;
    auto ans = sol.minEatingSpeed(piles, h);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Feasible speed.
Time Complexity:
O(n log Max)
Space Complexity:
O(1)
Key Idea:
BS on answer.
*/
