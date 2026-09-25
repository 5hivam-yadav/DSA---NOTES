/*
Problem: Check If Sorted
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Arrays
Statement: Given an integer array, return true if it is sorted in non-decreasing order, else false.
Sample Input: a = [1, 2, 2, 3, 5]
Sample Output: true
Explanation: Every element is >= the previous one.
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
    bool check(vector<int>& a) {
        int c = 0, n = a.size();
        for (int i = 0; i < n; i++) if (a[i] > a[(i + 1) % n]) c++;
        return c <= 1;
    }
};

int main() {
    vector<int> a = {1, 2, 2, 3, 5};

    Solution sol;
    auto ans = sol.check(a);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
Count breaks incl wrap.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Rotated sorted = 1 break.
*/
