/*
Problem: While Loops
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Basics
Statement: Given n, return the sum of its decimal digits using a while loop.
Sample Input: n = 472
Sample Output: 13
Explanation: 4 + 7 + 2 = 13.
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

int digitSum(int n) {
    int s = 0;
    while (n > 0) {
        s += n % 10;
        n /= 10;
    }
    return s;
}

int main() {
    int n = 472;

    auto ans = digitSum(n);
    cout << ans << endl;
    return 0;
}

/*
Approach:
1. Loop while n > 0.
2. Peel digit, shrink.
Time Complexity:
O(log n)
Space Complexity:
O(1)
Key Idea:
While loop for condition-based repetition.
*/
