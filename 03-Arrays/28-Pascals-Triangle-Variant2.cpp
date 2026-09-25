/*
Problem: Pascals Triangle Variant2
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP on Grids
Statement: Given row r and column c (1-indexed), return the element of Pascal's triangle at that position (nCr).
Sample Input: r = 5, c = 3
Sample Output: 6
Explanation: Row 5 is [1,4,6,4,1]; the 3rd value is 6.
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
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
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
