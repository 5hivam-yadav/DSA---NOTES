/*
Problem: Minimum Arrows
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Greedy
Statement: Given balloon intervals, find the minimum arrows to burst all (sort by end, shoot greedily).
Sample Input: points = [[10,16],[2,8],[1,6],[7,12]]
Sample Output: 2
Explanation: Arrows at 6 and 12 burst everything.
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
    int findMinArrowShots(vector<vector<int>>& p) {
        sort(p.begin(), p.end(), [](auto& a, auto& b) { return a[1] < b[1]; });
        int c = 0;
        long long last = LLONG_MIN;
        for (auto& b : p) {
            if (b[0] > last) {
                c++;
                last = b[1];
            }
        }
        return c;
    }
};

int main() {
    vector<vector<int>> points = {{10, 16}, {2, 8}, {1, 6}, {7, 12}};

    Solution sol;
    auto ans = sol.findMinArrowShots(points);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Shoot at end.
Time Complexity:
O(n log n)
Space Complexity:
O(1)
Key Idea:
Same as meetings.
*/
