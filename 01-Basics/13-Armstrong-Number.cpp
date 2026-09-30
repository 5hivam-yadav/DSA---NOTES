/*
Problem: Armstrong Number
Platform: GFG / Striver A2Z
Problem Number: -
Difficulty: Easy
Pattern: Maths
Statement: Given n, return true if it is an Armstrong number (sum of its digits
each raised to the digit count equals n). Sample Input: n = 153 Sample Output:
true Explanation: 1^3 + 5^3 + 3^3 = 153.
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

bool armstrong(int n) {
    int t = n, s = 0;
    while (t > 0) {
        int d = t % 10;
        s += d * d * d;
        t /= 10;
    }
    return s == n;
}

int main() {
    int n = 153;

    auto ans = armstrong(n);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
1. Sum cubes of digits.
2. Compare.
Time Complexity:
O(log10 n)
Space Complexity:
O(1)
Key Idea:
3-digit: cubes;
k-digit: kth powers.
*/
