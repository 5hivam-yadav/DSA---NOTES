/*
Problem: Swap Two Numbers
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Bit Manipulation
Statement: Given a and b, swap them and return the pair.
Sample Input: a = 3, b = 5
Sample Output: (5, 3)
Explanation: Values exchange places.
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

void xswap(int& a, int& b) {
    a ^= b;
    b ^= a;
    a ^= b;
}
  // Careful: same variable breaks; prefer std::swap.

int main() {
    int a = 3;
    int b = 5;

    xswap(a, b);
    // function returns nothing
    return 0;
}

/*
Approach:
XOR thrice.
Time Complexity:
O(1)
Space Complexity:
O(1)
Key Idea:
XOR swap.
*/
