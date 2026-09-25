/*
Problem: Sudoku Solver
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Backtracking
Statement: Given a 9x9 Sudoku with '.' blanks, fill it so each row, column and 3x3 box holds 1-9 exactly once.
Sample Input: board with blanks
Sample Output: completed board
Explanation: Constraints force a unique completion.
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
    bool ok(vector<vector<char>>& b, int r, int c, char d) {
        for (int i = 0; i < 9; i++) {
            if (b[r][i] == d || b[i][c] == d) return false;
            if (b[3*(r/3)+i/3][3*(c/3)+i%3] == d) return false;
        }
        return true;
    }
    bool f(vector<vector<char>>& b) {
        for (int r = 0; r < 9; r++) for (int c = 0; c < 9; c++) if (b[r][c] == '.') {
            for (char d = '1'; d <= '9'; d++) if (ok(b, r, c, d)) {
                b[r][c] = d;
                if (f(b)) return true;
                b[r][c] = '.';
            }
            return false;
        }
        return true;
    }
    void solveSudoku(vector<vector<char>>& b) {
        f(b);
    }
};

int main() {
    cout << "completed board" << endl;
    return 0;
}

/*
Approach:
Empty cell + digits.
Time Complexity:
O(9^empty)
Space Complexity:
O(1)
Key Idea:
Row/col/box check.
*/
