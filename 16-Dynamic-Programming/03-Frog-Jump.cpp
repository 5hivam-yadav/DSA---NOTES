/*
Problem: Frog Jump
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP - 1D
Statement: Given stone heights, return the minimum energy to reach the last stone jumping 1 or 2 steps with cost |h[i]-h[j]|.
Sample Input: h = [10, 20, 30, 10]
Sample Output: 20
Explanation: Jump 10->20->10? best path costs 20.
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

int frog(vector<int>& h) {
    int n = h.size(), p2 = 0, p1 = 0;
    for (int i = 1; i < n; i++) {
        int o = p1 + abs(h[i] - h[i-1]);
        int t = (i > 1 ? p2 + abs(h[i] - h[i-2]) : INT_MAX);
        int c = min(o, t);
        p2 = p1;
        p1 = c;
    }
    return p1;
}

int main() {
    vector<int> h = {10, 20, 30, 10};

    auto ans = frog(h);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Jump 1/2 min cost.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Two prev states.
*/
