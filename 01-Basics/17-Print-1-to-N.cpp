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

void f(int i, int n) {
    if (i > n)
        return;
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
