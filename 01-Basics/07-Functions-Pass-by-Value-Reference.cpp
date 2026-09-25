/*
Problem: Functions Pass by Value Reference
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Basics
Statement: Add two integers by value and swap two integers by reference to show value vs reference semantics.
Sample Input: a = 3, b = 5
Sample Output: add = 8, swapped = (5, 3)
Explanation: 3 + 5 = 8; references let the swap persist.
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

int add(int a, int b) {
    return a + b;
}
void doSwap(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}

int main() {
    int a = 3;
    int b = 5;

    doSwap(a, b);
    // function returns nothing
    return 0;
}

/*
Approach:
1. Value: copy in.
2. Reference (&): modify caller var.
Time Complexity:
O(1)
Space Complexity:
O(1)
Key Idea:
Use & to mutate, value to just compute.
*/
