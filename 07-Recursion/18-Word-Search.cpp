/*
Problem: Word Search
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Backtracking
Statement: Given a board and word, return true if the word traces 4-directionally without reusing cells.
Sample Input: board = [["A","B"],["C","D"]], word = "ABD"
Sample Output: true
Explanation: A(0,0)->B(0,1)->D(1,1) spells ABD.
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
    bool f(vector<vector<char>>& b, const string& w, int i, int r, int c) {
        if (i == (int)w.size()) return true;
        int R = b.size(), C = b[0].size();
        if (r < 0 || c < 0 || r >= R || c >= C || b[r][c] != w[i]) return false;
        char t = b[r][c];
        b[r][c] = '#';
        bool ok = f(b, w, i + 1, r + 1, c) || f(b, w, i + 1, r - 1, c) || f(b, w, i + 1, r, c + 1) || f(b, w, i + 1, r, c - 1);
        b[r][c] = t;
        return ok;
    }
    bool exist(vector<vector<char>>& b, string w) {
        for (size_t i = 0; i < b.size(); i++) for (size_t j = 0; j < b[0].size(); j++) if (f(b, w, 0, i, j)) return true;
        return false;
    }
};

int main() {
    vector<vector<char>> board = {{'A', 'B'}, {'C', 'D'}};
    string word = "ABD";

    Solution sol;
    auto ans = sol.exist(board, word);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
DFS + mark/unmark.
Time Complexity:
O(RC 4^L)
Space Complexity:
O(L)
Key Idea:
Backtrack grid.
*/
