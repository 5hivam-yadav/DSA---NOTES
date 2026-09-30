/*
Problem: Roman to Integer
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Strings
Statement: Given a Roman numeral string, convert it to an integer (subtract when
a smaller value precedes a larger one). Sample Input: s = "MCMXCIV" Sample
Output: 1994 Explanation: 1000 + (1000-100) + (100-10) + (5-1) = 1994.
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
    int romanToInt(string s) {
        unordered_map<char, int> v{{'I', 1},   {'V', 5},   {'X', 10},
                                   {'L', 50},  {'C', 100}, {'D', 500},
                                   {'M', 1000}};
        int ans = 0;
        for (size_t i = 0; i < s.size(); i++) {
            if (i + 1 < s.size() && v[s[i]] < v[s[i + 1]])
                ans -= v[s[i]];
            else
                ans += v[s[i]];
        }
        return ans;
    }
};

int main() {
    string s = "MCMXCIV";

    Solution sol;
    auto ans = sol.romanToInt(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Subtract if smaller before larger.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Prev-compare rule.
*/
