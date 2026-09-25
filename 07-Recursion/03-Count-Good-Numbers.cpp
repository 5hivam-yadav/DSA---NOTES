/*
Problem: Count Good Numbers
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Recursion
Statement: Given n, count good numbers of length n (even positions: 0,2,4,6,8; odd positions: 2,3,5,7) modulo 1e9+7.
Sample Input: n = 4
Sample Output: 400
Explanation: 5^2 * 4^2 = 25 * 16 = 400.
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
    const long long M = 1000000007LL;
    long long modPow(long long b, long long e) {
        long long r = 1;
        while (e) {
            if (e & 1) r = r * b % M;
            b = b * b % M;
            e >>= 1;
        }
        return r;
    }
    int countGoodNumbers(long long n) {
        long long e = (n + 1) / 2, o = n / 2;
        return (int)(modPow(5, e) * modPow(4, o) % M);
    }
};

int main() {
    long long n = 4;
    Solution sol;
    cout << sol.countGoodNumbers(n) << endl;
    return 0;
}

/*
Approach:
5^even * 4^odd mod.
Time Complexity:
O(log n)
Space Complexity:
O(1)
Key Idea:
Position parity.
*/
