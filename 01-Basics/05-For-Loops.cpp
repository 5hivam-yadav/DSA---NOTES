/*
Problem: For Loops
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Basics
Statement: Given n, return the sum of the first n natural numbers using a for
loop. Sample Input: n = 10 Sample Output: 55 Explanation: 1 + 2 + ... + 10 = 55.
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

int sumN(int n) {
    int s = 0;
    for (int i = 1; i <= n; i++)
        s += i;
    return s;
}

int main() {
    int n = 10;

    auto ans = sumN(n);
    cout << ans << endl;
    return 0;
}

/*
Approach:
1. Loop 1..n.
2. Accumulate.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
For loop for counted iteration.
*/
