/*
Problem: Subset Sum II Exists
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Backtracking
Statement: Given an array with duplicates and target, decide if any subset sums to target (sort + prune + take/skip).
Sample Input: a = [1,2,2,3], target = 5
Sample Output: true
Explanation: Subset [2,3] (or [1,2,2]) sums to 5.
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

bool f(int i, vector<int>& a, int t) {
    if (t == 0) return true;
    if (i == (int)a.size() || t < 0) return false;
    return f(i + 1, a, t - a[i]) || f(i + 1, a, t);
}
  // DP memo/tab optimizes to O(n*sum).

int main() {
    vector<int> a = {1, 2, 2, 3};
    int target = 5;
    cout << (f(0, a, target) ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
Take or skip.
Time Complexity:
O(2^n)
Space Complexity:
O(n)
Key Idea:
Decision tree.
*/
