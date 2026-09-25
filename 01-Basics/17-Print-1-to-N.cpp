/*
Problem: Print 1 to N
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Basics
Statement: Print integers from 1 to n using recursion.
Sample Input: n = 4
Sample Output: 1 2 3 4
Explanation: Each call prints i then recurses with i + 1.
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
    cout << i << ' ';
    f(i + 1, n);
}

/*
Approach:
1. Base i>n.
2. Print then recurse (head recursion prints ascending).
Time Complexity:
O(n)
Space Complexity:
O(n) stack
Key Idea:
Work before call = ascending.
*/
