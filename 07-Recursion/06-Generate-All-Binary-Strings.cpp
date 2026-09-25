/*
Problem: Generate All Binary Strings
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Recursion
Statement: Given n, generate all binary strings of length n with no consecutive 1s (or all 2^n if unconstrained).
Sample Input: n = 3
Sample Output: ["000","001","010","100","101"]
Explanation: Strings with adjacent 1s are excluded.
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

void f(int n, string cur, vector<string>& r) {
    if ((int)cur.size() == n) {
        r.push_back(cur);
        return;
    }
    f(n, cur + '0', r);
    if (cur.empty() || cur.back() != '1') f(n, cur + '1', r);
}

int main() {
    int n = 3;
    vector<string> r;
    f(n, "", r);
    for (size_t i = 0; i < r.size(); i++) cout << r[i] << (i + 1 < r.size() ? " " : "");
    cout << endl;
    return 0;
}

/*
Approach:
0 always, 1 if prev 0.
Time Complexity:
O(2^n)
Space Complexity:
O(n)
Key Idea:
Constrained choice.
*/
