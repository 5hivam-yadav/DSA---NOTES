/*
Problem: Largest Odd Number
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Strings
Statement: Given a numeric string, return the longest prefix forming an odd number.
Sample Input: num = "52"
Sample Output: "5"
Explanation: Dropping trailing 2 leaves odd 5.
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
    string largestOddNumber(string s) {
        for (int i = (int)s.size() - 1; i >= 0; i--) if ((s[i] - '0') % 2 == 1) return s.substr(0, i + 1);
        return "";
    }
};

int main() {
    string num = "52";

    Solution sol;
    auto ans = sol.largestOddNumber(num);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Scan right for odd.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Prefix to last odd.
*/
