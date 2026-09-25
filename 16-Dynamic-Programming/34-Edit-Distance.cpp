/*
Problem: Edit Distance
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: DP - Strings
Statement: Given words a and b, return the minimum insertions, deletions and replacements to convert a into b.
Sample Input: a = "horse", b = "ros"
Sample Output: 3
Explanation: horse -> rorse -> rose -> ros takes 3 edits.
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
    int minDistance(string a, string b) {
        int n = a.size(), m = b.size();
        vector<int> pr(m + 1), cu(m + 1);
        for (int j = 0; j <= m; j++) pr[j] = j;
        for (int i = 1; i <= n; i++) {
            cu[0] = i;
            for (int j = 1; j <= m; j++) cu[j] = (a[i-1] == b[j-1]) ? pr[j-1] : 1 + min({pr[j], cu[j-1], pr[j-1]});
            swap(pr, cu);
        }
        return pr[m];
    }
};

int main() {
    string a = "horse";
    string b = "ros";

    Solution sol;
    auto ans = sol.minDistance(a, b);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Insert/delete/replace +1.
Time Complexity:
O(nm)
Space Complexity:
O(m)
Key Idea:
Align ops.
*/
