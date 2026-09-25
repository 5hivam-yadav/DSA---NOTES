/*
Problem: Print Name N Times
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Basics
Statement: Print a fixed name n times using recursion (print, then recurse with i + 1).
Sample Input: n = 3
Sample Output: name printed 3 times
Explanation: Base case stops when i exceeds n.
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

void f(int i, int n) {
    if (i > n) return;
    cout << "Raj\n";
    f(i + 1, n);
}
  // call f(1, n)

/*
Approach:
1. Base i>n.
2. Print, recurse i+1.
Time Complexity:
O(n)
Space Complexity:
O(n) stack
Key Idea:
Base + work + smaller call.
*/
