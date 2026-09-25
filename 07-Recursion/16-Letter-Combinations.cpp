/*
Problem: Letter Combinations
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Recursion
Statement: Given phone digits 2-9, return all letter combinations per the telephone mapping.
Sample Input: digits = "23"
Sample Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
Explanation: 2 maps abc, 3 maps def; 3x3 combos.
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
    vector<string> m = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> ans;
    void f(int i, const string& d, string cur) {
        if (i == (int)d.size()) {
            ans.push_back(cur);
            return;
        }
        for (char c : m[d[i] - '0']) f(i + 1, d, cur + c);
    }
    vector<string> letterCombinations(string d) {
        if (d.empty()) return {};
        f(0, d, "");
        return ans;
    }
};

int main() {
    string digits = "23";

    Solution sol;
    auto ans = sol.letterCombinations(digits);
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Per-digit letters.
Time Complexity:
O(4^n)
Space Complexity:
O(n)
Key Idea:
Cartesian recurse.
*/
