/*
Problem: N Queens
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Backtracking
Statement: Given n, return all placements of n queens on an n x n board with no two attacking (columns and diagonals checked).
Sample Input: n = 4
Sample Output: [[".Q..", "...Q", "Q...", "..Q."], ["..Q.", "Q...", "...Q", ".Q.."]]
Explanation: The 4-queens puzzle has exactly these two solutions.
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
    vector<vector<string>> ans;
    bool ok(vector<string>& b, int r, int c) {
        int n = b.size();
        for (int i = 0; i < r; i++) if (b[i][c] == 'Q') return false;
        for (int i = r - 1, j = c - 1; i >= 0 && j >= 0; i--, j--) if (b[i][j] == 'Q') return false;
        for (int i = r - 1, j = c + 1; i >= 0 && j < n; i--, j++) if (b[i][j] == 'Q') return false;
        return true;
    }
    void f(int r, vector<string>& b) {
        int n = b.size();
        if (r == n) {
            ans.push_back(b);
            return;
        }
        for (int c = 0; c < n; c++) if (ok(b, r, c)) {
            b[r][c] = 'Q';
            f(r + 1, b);
            b[r][c] = '.';
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<string> b(n, string(n, '.'));
        f(0, b);
        return ans;
    }
};

int main() {
    int n = 4;

    Solution sol;
    auto ans = sol.solveNQueens(n);
    for (int i = 0; i < (int)ans.size(); i++) {
        for (int j = 0; j < (int)ans[i].size(); j++) cout << ans[i][j] << " ";
        cout << endl;
    }
    return 0;
}

/*
Approach:
Try col, check, undo.
Time Complexity:
O(n!)
Space Complexity:
O(n^2)
Key Idea:
Col+diag validity.
*/
