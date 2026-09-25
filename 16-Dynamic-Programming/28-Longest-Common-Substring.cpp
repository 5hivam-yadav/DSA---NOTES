/*
Problem: Longest Common Substring
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP - Strings
Statement: Given two strings, return the length of the longest common contiguous substring.
Sample Input: a = "abcjklp", b = "acjkp"
Sample Output: 3
Explanation: "cjk" is the longest shared block.
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

int lcsubstr(string a, string b) {
    int n = a.size(), m = b.size(), best = 0;
    vector<int> pr(m + 1, 0), cu(m + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cu[j] = (a[i-1] == b[j-1]) ? pr[j-1] + 1 : 0;
            best = max(best, cu[j]);
        }
        swap(pr, cu);
    }
    return best;
}

int main() {
    string a = "abcjklp";
    string b = "acjkp";

    auto ans = lcsubstr(a, b);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Reset on mismatch.
Time Complexity:
O(nm)
Space Complexity:
O(m)
Key Idea:
Contiguous needs reset.
*/
