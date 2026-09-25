/*
Problem: Rotate Matrix 90
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Arrays
Statement: Given an n x n matrix, rotate it 90 degrees clockwise in place (transpose, then reverse each row).
Sample Input: matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
Sample Output: [[7, 4, 1], [8, 5, 2], [9, 6, 3]]
Explanation: Transpose then reverse each row.
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
    void rotate(vector<vector<int>>& m) {
        int n = m.size();
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) swap(m[i][j], m[j][i]);
        for (int i = 0; i < n; i++) reverse(m[i].begin(), m[i].end());
    }
};

int main() {
    vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    Solution sol;
    sol.rotate(matrix);
    for (int i = 0; i < (int)matrix.size(); i++) {
        for (int j = 0; j < (int)matrix[i].size(); j++) cout << matrix[i][j] << " ";
        cout << endl;
    }
    return 0;
}

/*
Approach:
Transpose + reverse.
Time Complexity:
O(n^2)
Space Complexity:
O(1)
Key Idea:
90 = transpose + mirror.
*/
