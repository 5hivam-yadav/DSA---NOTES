/*
Problem: First and Last Occurrence
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Search
Statement: Given a sorted array and x, return the first and last index of x, or [-1, -1] if absent.
Sample Input: a = [5, 7, 7, 8, 8, 10], x = 8
Sample Output: [3, 4]
Explanation: 8 spans indices 3 to 4.
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
    vector<int> searchRange(vector<int>& a, int x) {
        auto l = lower_bound(a.begin(), a.end(), x);
        auto r = upper_bound(a.begin(), a.end(), x);
        if (l == a.end() || *l != x) return { -1, -1};
        return { (int)(l - a.begin()), (int)(r - a.begin()) - 1};
    }
};

int main() {
    vector<int> a = {5, 7, 7, 8, 8, 10};
    int x = 8;

    Solution sol;
    auto ans = sol.searchRange(a, x);
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
lower/upper bound.
Time Complexity:
O(log n)
Space Complexity:
O(1)
Key Idea:
Bounds give range.
*/
