/*
Problem: Count Digits
Platform: GFG / Striver A2Z
Problem Number: -
Difficulty: Easy
Pattern: Basics
Statement: Given an integer n, count how many digits it contains. The number 0 has one digit.
Sample Input: n = 7789
Sample Output: 4
Explanation: 7789 has four digits: 7, 7, 8, 9.
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

int countDigits(int n) {
    if (n == 0) return 1;
    int c = 0;
    while (n > 0) {
        c++;
        n /= 10;
    }
    return c;
}

int main() {
    int n = 7789;

    auto ans = countDigits(n);
    cout << ans << endl;
    return 0;
}

/*
Approach:
1. Handle 0.
2. Divide by 10, count.
Time Complexity:
O(log10 n)
Space Complexity:
O(1)
Key Idea:
Digit count = log10.
*/
