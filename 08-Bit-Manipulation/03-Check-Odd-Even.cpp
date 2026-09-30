/*
Problem: Check Odd Even
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Bit Manipulation
Statement: Given n, return Odd or Even using n % 2 (or the lowest bit).
Sample Input: n = 7
Sample Output: Odd
Explanation: 7 % 2 = 1.
*/
#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

bool isOdd(int n) { return n & 1; }

int main() {
    int n = 7;

    auto ans = isOdd(n);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
LSB decides.
Time Complexity:
O(1)
Space Complexity:
O(1)
Key Idea:
&1 parity.
*/
