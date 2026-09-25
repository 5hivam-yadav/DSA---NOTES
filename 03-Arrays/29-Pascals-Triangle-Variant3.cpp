/*
Problem: Pascals Triangle Variant3
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP on Grids
Statement: Given n, return the first n rows of Pascal's triangle where each entry is the sum of the two above it.
Sample Input: n = 5
Sample Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
Explanation: Each row is built from the previous one.
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
    vector<vector<int>> generate(int n) {
        vector<vector<int>> t(n);
        for (int i = 0; i < n; i++) {
            t[i].assign(i + 1, 1);
            for (int j = 1; j < i; j++) t[i][j] = t[i - 1][j - 1] + t[i - 1][j];
        }
        return t;
    }
};

int main() {
    int n = 5;

    Solution sol;
    auto ans = sol.generate(n);
    for (int i = 0; i < (int)ans.size(); i++) {
        for (int j = 0; j < (int)ans[i].size(); j++) cout << ans[i][j] << " ";
        cout << endl;
    }
    return 0;
}

/*
Approach:
Sum of two above.
Time Complexity:
O(n^2)
Space Complexity:
O(n^2)
Key Idea:
DP triangle.
*/
