/*
Problem: Print N to 1
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Basics
Statement: Print integers from n down to 1 using recursion.
Sample Input: n = 4
Sample Output: 4 3 2 1
Explanation: Each call prints n then recurses with n - 1.
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

void f(int n) {
    if (n == 0) return;
    cout << n << ' ';
    f(n - 1);
}

int main() {
    int n = 4;

    f(n);
    // function returns nothing
    return 0;
}

/*
Approach:
1. Base 0.
2. Print then recurse.
Time Complexity:
O(n)
Space Complexity:
O(n) stack
Key Idea:
Print before shrinking call.
*/
