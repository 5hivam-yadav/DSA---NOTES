/*
Problem: Check Prime
Platform: GFG / LeetCode
Problem Number: -
Difficulty: Easy
Pattern: Maths
Statement: Given n, return true if n is prime (greater than 1, divisible only by
1 and itself). Sample Input: n = 17 Sample Output: true Explanation: 17 has no
divisors besides 1 and 17.
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

bool isPrime(int n) {
    if (n < 2)
        return false;
    for (int i = 2; 1LL * i * i <= n; i++)
        if (n % i == 0)
            return false;
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
