/*
Problem: Search in 2D I Flat
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search
Statement: Given an m x n matrix with rows sorted and each row's first element greater than the previous row's last, search target in O(log(mn)) by treating it flat.
Sample Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
Sample Output: true
Explanation: 3 is at row 0, column 1.
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
        if (m.empty()) return false;
        int R = m.size(), C = m[0].size(), lo = 0, hi = R * C - 1;
        while (lo <= hi) {
            int mm = lo + (hi - lo) / 2, v = m[mm / C][mm % C];
            if (v == x) return true;
            else if (v < x) lo = mm + 1;
            else hi = mm - 1;
        }
        return false;
    }
};

int main() {
    vector<vector<int>> matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    int target = 3;

    Solution sol;
    auto ans = sol.searchMatrix(matrix, target);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
Flatten index.
Time Complexity:
O(log mn)
Space Complexity:
O(1)
Key Idea:
Row-major sorted.
*/
