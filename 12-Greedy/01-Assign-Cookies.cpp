/*
Problem: Assign Cookies
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Greedy
Statement: Given greed factors and cookie sizes, maximize content children by
matching smallest sufficient cookie (greedy sort). Sample Input: g = [1,2,3], s
= [1,1] Sample Output: 1 Explanation: Only one child can be satisfied.
*/
#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
  public:
    int findContentChildren(vector<int> &g, vector<int> &s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int i = 0, j = 0;
        while (i < (int)g.size() && j < (int)s.size()) {
            if (s[j] >= g[i])
                i++;
            j++;
        }
        return i;
    }
};

int main() {
    vector<int> g = {1, 2, 3};
    vector<int> s = {1, 1};

    Solution sol;
    auto ans = sol.findContentChildren(g, s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Smallest fit.
Time Complexity:
O(n log n)
Space Complexity:
O(1)
Key Idea:
Two pointers.
*/
