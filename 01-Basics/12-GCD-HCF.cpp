/*
Problem: GCD HCF
Platform: GFG / Striver A2Z
Problem Number: -
Difficulty: Easy
Pattern: Maths
Statement: Given two integers a and b, return their greatest common divisor; LCM follows as a / gcd * b.
Sample Input: a = 36, b = 60
Sample Output: 12
Explanation: The largest integer dividing both is 12.
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

long long gcdll(long long a, long long b) {
    while (b) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}
long long lcml(long long a, long long b) {
    return a / gcdll(a, b) * b;
}

/*
Approach:
1. Euclid loop.
2. LCM via GCD.
Time Complexity:
O(log min(a, b))
Space Complexity:
O(1)
Key Idea:
Euclid remainder shrinks fast.
*/
