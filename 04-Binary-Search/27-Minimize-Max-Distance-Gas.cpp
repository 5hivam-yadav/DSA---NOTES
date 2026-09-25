/*
Problem: Minimize Max Distance Gas
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Search on Answer
Statement: Given station positions and k new stations, minimize the maximum gap (binary search on precision answer).
Sample Input: stations = [1,2,3,4,5], k = 4
Sample Output: 0.5
Explanation: Doubling stations halves every gap to 0.5.
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
    bool ok(vector<int>& s, int k, double d) {
        int need = 0;
        for (size_t i = 1; i < s.size(); i++) need += (int)((s[i] - s[i - 1]) / d);
        return need <= k;
    }
    double minmaxGasDist(vector<int>& s, int k) {
        double lo = 0, hi = 1e8;
        for (int i = 0; i < 100; i++) {
            double m = (lo + hi) / 2;
            if (ok(s, k, m)) hi = m;
            else lo = m;
        }
        return hi;
    }
};

/*
Approach:
Stations needed.
Time Complexity:
O(n log precision)
Space Complexity:
O(1)
Key Idea:
Double BS.
*/
