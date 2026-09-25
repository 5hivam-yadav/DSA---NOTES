/*
Problem: Row with Max 1s
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Search
Statement: Given a binary matrix with each row sorted (0s then 1s), return the row index with the most 1s.
Sample Input: mat = [[0,1,1,1],[0,0,1,1],[1,1,1,1]]
Sample Output: 2
Explanation: Row 2 has four 1s, the most.
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

int rowMax1(vector<vector<int>>& m) {
    int R = m.size(), C = m[0].size(), best = 0, r = 0;
    for (int i = 0; i < R; i++) {
        int f = lower_bound(m[i].begin(), m[i].end(), 1) - m[i].begin();
        if (C - f > C - (lower_bound(m[best].begin(), m[best].end(), 1) - m[best].begin())) {
            best = i;
        }
    }
    return best;
}
  // Optimal O(m+n) from top-right.

int main() {
    vector<vector<int>> mat = {{0, 1, 1, 1}, {0, 0, 1, 1}, {1, 1, 1, 1}};

    auto ans = rowMax1(mat);
    cout << ans << endl;
    return 0;
}

/*
Approach:
lower_bound per row.
Time Complexity:
O(m log n)
Space Complexity:
O(1)
Key Idea:
First 1 per row.
*/
