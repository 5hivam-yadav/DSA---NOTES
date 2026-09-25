/*
Problem: Integer to Roman
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Strings
Statement: Given an integer 1..3999, convert it to a Roman numeral using greedy value-symbol pairs.
Sample Input: num = 1994
Sample Output: "MCMXCIV"
Explanation: 1000 + 900 + 90 + 4 = MCMXCIV.
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
    string intToRoman(int n) {
        vector<pair<int, string>> v{
            {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"},
            {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
        };
        string r;
        for (auto& p : v) while (n >= p.first) {
            r += p.second;
            n -= p.first;
        }
        return r;
    }
};

int main() {
    int num = 1994;

    Solution sol;
    auto ans = sol.intToRoman(num);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Greedy table.
Time Complexity:
O(1)
Space Complexity:
O(1)
Key Idea:
Largest-fit table.
*/
