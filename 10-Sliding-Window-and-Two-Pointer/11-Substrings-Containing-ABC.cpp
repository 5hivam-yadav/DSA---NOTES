/*
Problem: Substrings Containing Abc
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Sliding Window
Statement: Given a string of a/b/c, count substrings containing at least one of each (for each right, add left+1 once valid).
Sample Input: s = "abcabc"
Sample Output: 10
Explanation: Ten windows contain a, b and c.
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
    int numberOfSubstrings(string s) {
        int last[3] = {-1, -1, -1}, ans = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            last[s[i] - 'a'] = i;
            ans += 1 + min({last[0], last[1], last[2]});
        }
        return ans;
    }
};

int main() {
    string s = "abcabc";

    Solution sol;
    auto ans = sol.numberOfSubstrings(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Add 1+min-last.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Last positions.
*/
