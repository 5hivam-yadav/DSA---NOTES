/*
Problem: Search in 2D II Row Col
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search
Statement: Given a matrix with rows and columns sorted ascending, search target in O(m+n) starting from the top-right corner.
Sample Input: matrix = [[1,4,7,11],[2,5,8,12],[3,6,9,16]], target = 5
Sample Output: true
Explanation: 5 is at row 1, column 1.
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
    bool searchMatrix(vector<vector<int>>& m, int x) {
        int R = m.size(), C = m[0].size(), r = 0, c = C - 1;
        while (r < R && c >= 0) {
            if (m[r][c] == x) return true;
            else if (m[r][c] < x) r++;
            else c--;
        }
        return false;
    }
};

int main() {
    vector<vector<int>> matrix = {{1, 4, 7, 11}, {2, 5, 8, 12}, {3, 6, 9, 16}};
    int target = 5;

    Solution sol;
    auto ans = sol.searchMatrix(matrix, target);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
Top-right walk.
Time Complexity:
O(m+n)
Space Complexity:
O(1)
Key Idea:
Staircase.
*/
