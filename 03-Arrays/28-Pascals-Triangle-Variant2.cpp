/*
Problem: Pascals Triangle Variant2
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP on Grids
Statement: Given row r and column c (1-indexed), return the element of Pascal's
triangle at that position (nCr). Sample Input: r = 5, c = 3 Sample Output: 6
Explanation: Row 5 is [1,4,6,4,1]; the 3rd value is 6.
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

vector<long long> pascalRow(int n) {
    vector<long long> row(n);
    long long c = 1;
    for (int k = 1; k <= n; k++) {
        row[k - 1] = c;
        c = c * (n - k) / k;
    }
    return row;
}

int main() {
    int r = 5;
    int c = 3;

    auto ans = pascalRow(r);
    for (int i = 0; i < (int)ans.size(); i++)
        cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Roll C(n, k).
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Next from prev.
*/
