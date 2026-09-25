/*
Problem: Set Matrix Zeroes
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Arrays
Statement: Given an m x n matrix, set the entire row and column to zero wherever a zero appears, in place with O(1) space.
Sample Input: matrix = [[1, 1, 1], [1, 0, 1], [1, 1, 1]]
Sample Output: [[1, 0, 1], [0, 0, 0], [1, 0, 1]]
Explanation: Row 1 and column 1 are zeroed.
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
    void setZeroes(vector<vector<int>>& m) {
        int R = m.size(), C = m[0].size();
        bool f0 = false;
        for (int i = 0; i < R; i++) {
            if (m[i][0] == 0) f0 = true;
            for (int j = 1; j < C; j++) if (m[i][j] == 0) m[i][0] = m[0][j] = 0;
        }
        for (int i = 1; i < R; i++) for (int j = 1; j < C; j++) if (m[i][0] == 0 || m[0][j] == 0) m[i][j] = 0;
        if (m[0][0] == 0) for (int j = 0; j < C; j++) m[0][j] = 0;
        if (f0) for (int i = 0; i < R; i++) m[i][0] = 0;
    }
};

int main() {
    vector<vector<int>> matrix = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};

    Solution sol;
    sol.setZeroes(matrix);
    for (int i = 0; i < (int)matrix.size(); i++) {
        for (int j = 0; j < (int)matrix[i].size(); j++) cout << matrix[i][j] << " ";
        cout << endl;
    }
    return 0;
}

/*
Approach:
First row/col markers.
Time Complexity:
O(mn)
Space Complexity:
O(1)
Key Idea:
In-place markers.
*/
