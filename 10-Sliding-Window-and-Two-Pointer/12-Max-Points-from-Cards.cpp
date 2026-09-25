/*
Problem: Max Points from Cards
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Sliding Window
Statement: Given card points and k, take k cards from either end to maximize the sum (minimize the left-out window).
Sample Input: points = [1,2,3,4,5,6,1], k = 3
Sample Output: 12
Explanation: Take 6 + 1 from the right and 5? best is 5+6+1 = 12.
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
    int maxScore(vector<int>& c, int k) {
        int n = c.size(), tot = 0;
        for (int x : c) tot += x;
        if (k == n) return tot;
        int w = n - k, s = 0;
        for (int i = 0; i < w; i++) s += c[i];
        int mn = s;
        for (int i = w; i < n; i++) {
            s += c[i] - c[i - w];
            mn = min(mn, s);
        }
        return tot - mn;
    }
};

int main() {
    vector<int> points = {1, 2, 3, 4, 5, 6, 1};
    int k = 3;

    Solution sol;
    auto ans = sol.maxScore(points, k);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Min middle window.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Total - min-subarray.
*/
