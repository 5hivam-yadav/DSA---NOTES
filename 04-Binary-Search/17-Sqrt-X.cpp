/*
Problem: Sqrt X
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Search
Statement: Given non-negative x, return floor(sqrt(x)) without library pow (binary search).
Sample Input: x = 8
Sample Output: 2
Explanation: sqrt(8) is about 2.83, floored to 2.
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
    int mySqrt(int x) {
        long long lo = 0, hi = x;
        while (lo <= hi) {
            long long m = lo + (hi - lo) / 2;
            if (m * m == x) return (int)m;
            else if (m * m < x) lo = m + 1;
            else hi = m - 1;
        }
        return (int)hi;
    }
};

int main() {
    int x = 8;

    Solution sol;
    auto ans = sol.mySqrt(x);
    cout << ans << endl;
    return 0;
}

/*
Approach:
BS 0..x.
Time Complexity:
O(log x)
Space Complexity:
O(1)
Key Idea:
Square predicate.
*/
