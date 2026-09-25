/*
Problem: Reverse Words
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Strings
Statement: Given a string with words separated by spaces, reverse the word order and collapse extra spaces.
Sample Input: s = "the sky is blue"
Sample Output: "blue is sky the"
Explanation: Words run in reverse order, single-spaced.
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
    string reverseWords(string s) {
        reverse(s.begin(), s.end());
        int n = s.size(), i = 0;
        string r;
        while (i < n) {
            while (i < n && s[i] == ' ') i++;
            int j = i;
            while (j < n && s[j] != ' ') j++;
            if (i < j) {
                string wd = s.substr(i, j - i);
                reverse(wd.begin(), wd.end());
                if (!r.empty()) r += ' ';
                r += wd;
                i = j;
            }
        }
        return r;
    }
};

int main() {
    string s = "the sky is blue";

    Solution sol;
    auto ans = sol.reverseWords(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Reverse all then words.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Double reverse.
*/
