/*
Problem: Spiral Matrix
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Arrays
Statement: Given an m x n matrix, return all elements in clockwise spiral order from the top-left.
Sample Input: matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
Sample Output: [1, 2, 3, 6, 9, 8, 7, 4, 5]
Explanation: Peel the outer ring, then the inner part.
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
    vector<int> spiralOrder(vector<vector<int>>& m) {
        vector<int> r;
        int t = 0, b = (int)m.size() - 1, l = 0, rr = (int)m[0].size() - 1;
        while (t <= b && l <= rr) {
            for (int j = l; j <= rr; j++) r.push_back(m[t][j]);
            t++;
            for (int i = t; i <= b; i++) r.push_back(m[i][rr]);
            rr--;
            if (t <= b) {
                for (int j = rr; j >= l; j--) r.push_back(m[b][j]);
                b--;
            }
            if (l <= rr) {
                for (int i = b; i >= t; i--) r.push_back(m[i][l]);
                l++;
            }
        }
        return r;
    }
};

int main() {
    vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    Solution sol;
    auto ans = sol.spiralOrder(matrix);
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Peel 4 walls.
Time Complexity:
O(mn)
Space Complexity:
O(1) extra
Key Idea:
Boundary shrink.
*/
