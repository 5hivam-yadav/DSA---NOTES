/*
Problem: Capacity to Ship Packages
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Search on Answer
Statement: Given package weights and D days, find the minimum ship capacity to deliver within D days (binary search on capacity).
Sample Input: weights = [1,2,3,4,5,6,7,8,9,10], D = 5
Sample Output: 15
Explanation: Capacity 15 ships in exactly 5 days.
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
    bool ok(vector<int>& w, int d, int cap) {
        int days = 1, load = 0;
        for (int x : w) {
            if (load + x > cap) {
                days++;
                load = 0;
            }
            load += x;
        }
        return days <= d;
    }
    int shipWithinDays(vector<int>& w, int d) {
        int lo = *max_element(w.begin(), w.end()), hi = accumulate(w.begin(), w.end(), 0);
        while (lo < hi) {
            int m = lo + (hi - lo) / 2;
            if (ok(w, d, m)) hi = m;
            else lo = m + 1;
        }
        return lo;
    }
};

/*
Approach:
Days feasibility.
Time Complexity:
O(n log Sum)
Space Complexity:
O(1)
Key Idea:
Capacity BS.
*/
