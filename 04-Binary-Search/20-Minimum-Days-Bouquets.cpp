/*
Problem: Minimum Days Bouquets
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Search on Answer
Statement: Given bloomDay, m bouquets and k adjacent flowers per bouquet, return the minimum day to make all m bouquets, or -1 if impossible (binary search on the answer).
Sample Input: bloomDay = [1,10,3,10,2], m = 3, k = 1
Sample Output: 3
Explanation: By day 3 the flowers at indices 0, 2, 4 bloom; three runs of length 1 give the 3 bouquets.
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
    bool ok(vector<int>& b, int d, int m, int k) {
        int c = 0, run = 0;
        for (int x : b) {
            if (x <= d) {
                if (++run == k) {
                    c++;
                    run = 0;
                }
            }
            else run = 0;
        }
        return c >= m;
    }
    int minDays(vector<int>& b, int m, int k) {
        long long need = 1LL * m * k;
        if ((long long)b.size() < need) return -1;
        int lo = 1, hi = 1e9;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (ok(b, mid, m, k)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};

/*
Approach:
Bloom-day feasibility.
Time Complexity:
O(n log Max)
Space Complexity:
O(1)
Key Idea:
Count k-runs.
*/
