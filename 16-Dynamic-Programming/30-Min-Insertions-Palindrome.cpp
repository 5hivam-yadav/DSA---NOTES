/*
Problem: Min Insertions Palindrome
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Dynamic Programming
Statement: Given s, return the minimum insertions to make it a palindrome (n - longest palindromic subsequence).
Sample Input: s = "mbadm"
Sample Output: 2
Explanation: LPS length 3; 5 - 3 = 2.
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

class Solution {
public:
    int minInsertions(string s) {
        string r = s;
        reverse(r.begin(), r.end());
        int n = s.size();
        vector<int> pr(n + 1, 0), cu(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) cu[j] = (s[i-1] == r[j-1]) ? pr[j-1] + 1 : max(pr[j], cu[j-1]);
            swap(pr, cu);
        }
        return n - pr[n];
    }
};

int main() {
    string s = "mbadm";

    Solution sol;
    auto ans = sol.minInsertions(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
n - LPS.
Time Complexity:
O(n^2)
Space Complexity:
O(n)
Key Idea:
Keep LPS, insert rest.
*/
