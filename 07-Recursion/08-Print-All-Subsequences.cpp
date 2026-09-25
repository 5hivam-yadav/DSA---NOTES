/*
Problem: Print All Subsequences
Platform: LeetCode
Problem Number: -
Difficulty: Easy
Pattern: Recursion
Statement: Given an array, print all its subsequences via take/skip recursion.
Sample Input: a = [1,2]
Sample Output: [[],[1],[2],[1,2]]
Explanation: Each element is taken or skipped.
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

void f(int i, vector<int>& a, vector<int>& ds, vector<vector<int>>& r) {
    if (i == (int)a.size()) {
        r.push_back(ds);
        return;
    }
    ds.push_back(a[i]);
    f(i + 1, a, ds, r);
    ds.pop_back();
    f(i + 1, a, ds, r);
}

int main() {
    vector<int> a = {1, 2};
    vector<int> ds;
    vector<vector<int>> r;
    f(0, a, ds, r);
    for (size_t i = 0; i < r.size(); i++) {
        for (size_t j = 0; j < r[i].size(); j++) cout << r[i][j] << (j + 1 < r[i].size() ? " " : "");
        cout << endl;
    }
    return 0;
}

/*
Approach:
Take then skip + undo.
Time Complexity:
O(2^n n)
Space Complexity:
O(n)
Key Idea:
Choice tree.
*/
