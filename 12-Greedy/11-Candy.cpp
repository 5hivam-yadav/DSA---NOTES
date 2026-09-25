/*
Problem: Candy
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Greedy
Statement: Given child ratings, assign minimum candies so higher-rated neighbours get more (two passes, max of both sides).
Sample Input: ratings = [1,0,2]
Sample Output: 5
Explanation: Distribution [2,1,2] sums to 5.
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
    int candy(vector<int>& r) {
        int n = r.size();
        vector<int> c(n, 1);
        for (int i = 1; i < n; i++) if (r[i] > r[i-1]) c[i] = c[i-1] + 1;
        for (int i = n - 2; i >= 0; i--) if (r[i] > r[i+1]) c[i] = max(c[i], c[i+1] + 1);
        return accumulate(c.begin(), c.end(), 0);
    }
};

int main() {
    vector<int> ratings = {1, 0, 2};

    Solution sol;
    auto ans = sol.candy(ratings);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Two passes.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Left + right rules.
*/
