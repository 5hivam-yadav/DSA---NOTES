/*
Problem: Remove K Digits
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Monotonic Stack
Statement: Given numeric string num and k, remove k digits to form the smallest possible number (monotonic stack, strip leading zeros).
Sample Input: num = "1432219", k = 3
Sample Output: "1219"
Explanation: Removing 4, 3, 2 leaves the minimum 1219.
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
    string removeKdigits(string s, int k) {
        string st;
        for (char c : s) {
            while (!st.empty() && k > 0 && st.back() > c) {
                st.pop_back();
                k--;
            }
            st += c;
        }
        while (k-- > 0 && !st.empty()) st.pop_back();
        int i = 0;
        while (i < (int)st.size() && st[i] == '0') i++;
        string r = st.substr(i);
        return r.empty() ? "0" : r;
    }
};

int main() {
    string num = "1432219";
    int k = 3;

    Solution sol;
    auto ans = sol.removeKdigits(num, k);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Mono inc + strip zeros.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Pop bigger before.
*/
