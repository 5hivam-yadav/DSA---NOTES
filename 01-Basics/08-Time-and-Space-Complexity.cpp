/*
Problem: Time and Space Complexity
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Basics
Statement: Given an array and x, find x with linear search; analysis is O(n) time and O(1) space.
Sample Input: a = [4, 2, 7, 1], x = 7
Sample Output: 2
Explanation: 7 is at index 2 after scanning from the left.
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

int linearSearch(vector<int>& a, int x) {
    for (int i = 0; i < (int)a.size(); i++) if (a[i] == x) return i;
    return -1;
}
  // O(n) time (scan), O(1) space. Rules: drop constants, keep dominant term.
  // O(1) < O(log n) < O(n) < O(n log n) < O(n^2) < O(2^n).

int main() {
    vector<int> a = {4, 2, 7, 1};
    int x = 7;

    auto ans = linearSearch(a, x);
    cout << ans << endl;
    return 0;
}

/*
Approach:
1. Count basic ops vs n.
2. Drop constants.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Complexity = growth rate of ops/memory.
*/
