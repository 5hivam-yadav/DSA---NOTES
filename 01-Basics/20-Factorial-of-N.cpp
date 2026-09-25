/*
Problem: Factorial of N
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Maths
Statement: Given n, return n! with 0! = 1, using recursion n * (n-1)!.
Sample Input: n = 5
Sample Output: 120
Explanation: 5 * 4 * 3 * 2 * 1 = 120.
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

long long fact(int n) {
    if (n <= 1) return 1;
    return 1LL * n * fact(n - 1);
}

int main() {
    int n = 5;

    auto ans = fact(n);
    cout << ans << endl;
    return 0;
}

/*
Approach:
1. Base 0/1.
2. n*f(n-1).
Time Complexity:
O(n)
Space Complexity:
O(n) stack
Key Idea:
Recursive definition of factorial.
*/
