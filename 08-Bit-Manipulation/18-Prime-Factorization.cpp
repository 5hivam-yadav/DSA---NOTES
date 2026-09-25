/*
Problem: Prime Factorization
Platform: GFG / LeetCode
Problem Number: -
Difficulty: Easy
Pattern: Maths
Statement: Given n, return its prime factors with multiplicity by trial division up to sqrt(n).
Sample Input: n = 60
Sample Output: [2, 2, 3, 5]
Explanation: 2 x 2 x 3 x 5 = 60.
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

vector<int> spf(int n) {
    vector<int> s(n + 1);
    for (int i = 2; i <= n; i++) if (!s[i]) {
        s[i] = i;
        if (1LL * i * i <= n) for (long long j = 1LL * i * i; j <= n; j += i) if (!s[j]) s[j] = i;
    }
    return s;
}
vector<int> factorize(int x, vector<int>& s) {
    vector<int> r;
    while (x > 1) {
        r.push_back(s[x]);
        x /= s[x];
    }
    return r;
}

/*
Approach:
SPF then divide.
Time Complexity:
O(n log log n + log x)
Space Complexity:
O(n)
Key Idea:
Smallest prime table.
*/
