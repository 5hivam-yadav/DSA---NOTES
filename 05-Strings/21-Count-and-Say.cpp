/*
Problem: Count and Say
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Strings
Statement: Given n, return the n-th count-and-say string by reading off runs of the previous term.
Sample Input: n = 4
Sample Output: "1211"
Explanation: 1 -> 11 -> 21 -> 1211 by describing runs.
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
    string countAndSay(int n) {
        string cur = "1";
        for (int k = 2; k <= n; k++) {
            string nxt;
            for (size_t i = 0; i < cur.size(); ) {
                size_t j = i;
                while (j < cur.size() && cur[j] == cur[i]) j++;
                nxt += to_string(j - i);
                nxt += cur[i];
                i = j;
            }
            cur.swap(nxt);
        }
        return cur;
    }
};

int main() {
    int n = 4;

    Solution sol;
    auto ans = sol.countAndSay(n);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Run-length encode previous term iteratively.
Time Complexity:
O(n * len)
Space Complexity:
O(len)
Key Idea:
Group equal digits, append count+digit.
*/
