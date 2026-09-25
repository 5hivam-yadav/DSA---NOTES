/*
Problem: Check Prime
Platform: GFG / LeetCode
Problem Number: -
Difficulty: Easy
Pattern: Maths
Statement: Given n, return true if n is prime (greater than 1, divisible only by 1 and itself).
Sample Input: n = 17
Sample Output: true
Explanation: 17 has no divisors besides 1 and 17.
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

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; 1LL * i * i <= n; i++) if (n % i == 0) return false;
    return true;
}

int main() {
    int n = 17;

    auto ans = isPrime(n);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
1. n<2 false.
2. Trial to sqrt.
Time Complexity:
O(sqrt n)
Space Complexity:
O(1)
Key Idea:
Composite has factor <= sqrt.
*/
