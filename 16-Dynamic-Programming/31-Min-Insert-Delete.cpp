/*
Problem: Min Insert Delete
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP - Strings
Statement: Given strings a and b, return min insertions + deletions converting a to b (n + m - 2*LCS).
Sample Input: a = "sea", b = "eat"
Sample Output: 2
Explanation: LCS length 2; ops = 3+3-4 = 2.
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

int minOps(string a, string b) {
    int n = a.size(), m = b.size();
    vector<int> pr(m + 1, 0), cu(m + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) cu[j] = (a[i-1] == b[j-1]) ? pr[j-1] + 1 : max(pr[j], cu[j-1]);
        swap(pr, cu);
    }
    int l = pr[m];
    return (n - l) + (m - l);
}

int main() {
    string a = "sea";
    string b = "eat";

    auto ans = minOps(a, b);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Keep LCS.
Time Complexity:
O(nm)
Space Complexity:
O(m)
Key Idea:
Delete + insert rest.
*/
