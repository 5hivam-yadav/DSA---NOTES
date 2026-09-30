/*
Problem: Kth Permutation
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Backtracking
Statement: Given n and k, return the k-th permutation of 1..n using factorials
to pick each digit. Sample Input: n = 3, k = 3 Sample Output: "213" Explanation:
Ordered permutations: 123, 132, 213.
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
    string getPermutation(int n, int k) {
        vector<int> a;
        for (int i = 1; i <= n; i++)
            a.push_back(i);
        vector<int> fact(n + 1, 1);
        for (int i = 1; i <= n; i++)
            fact[i] = fact[i - 1] * i;
        k--;
        string r;
        for (int i = n; i >= 1; i--) {
            int idx = k / fact[i - 1];
            r += to_string(a[idx]);
            a.erase(a.begin() + idx);
            k %= fact[i - 1];
        }
        return r;
    }
};

int main() {
    int n = 3;
    int k = 3;

    Solution sol;
    auto ans = sol.getPermutation(n, k);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Factorial blocks.
Time Complexity:
O(n^2)
Space Complexity:
O(n)
Key Idea:
k selects block.
*/
