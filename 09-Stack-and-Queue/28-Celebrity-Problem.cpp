/*
Problem: Celebrity Problem
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Stack
Statement: Given an acquaintance matrix, find the celebrity (known by all, knows none) in O(n) with elimination + verification.
Sample Input: M = [[0,1,0],[0,0,0],[0,1,0]]
Sample Output: 1
Explanation: Person 1 is known by all and knows nobody.
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

int celebrity(vector<vector<int>>& m) {
    int n = m.size(), c = 0;
    for (int i = 1; i < n; i++) if (m[c][i]) c = i;
    for (int i = 0; i < n; i++) {
        if (i == c) continue;
        if (m[c][i] || !m[i][c]) return -1;
    }
    return c;
}

int main() {
    vector<vector<int>> M = {{0, 1, 0}, {0, 0, 0}, {0, 1, 0}};

    auto ans = celebrity(M);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Eliminate + verify.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Knows-nobody check.
*/
