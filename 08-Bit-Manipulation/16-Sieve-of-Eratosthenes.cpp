/*
Problem: Sieve of Eratosthenes
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Maths
Statement: Given n, return all primes up to n by sieving multiples from 2
upward. Sample Input: n = 10 Sample Output: [2, 3, 5, 7] Explanation: Composites
are crossed out, primes remain.
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

class Solution {
  public:
    int countPrimes(int n) {
        if (n <= 2)
            return 0;
        vector<char> p(n, 1);
        p[0] = p[1] = 0;
        for (int i = 2; 1LL * i * i < n; i++)
            if (p[i])
                for (int j = i * i; j < n; j += i)
                    p[j] = 0;
        return count(p.begin(), p.end(), 1);
    }
};

int main() {
    int n = 10;

    Solution sol;
    auto ans = sol.countPrimes(n);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Strike multiples from i*i.
Time Complexity:
O(n log log n)
Space Complexity:
O(n)
Key Idea:
Composite marking.
*/
