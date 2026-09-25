/*
Problem: Repeated String Match
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Strings
Statement: Given strings a and b, return the minimum repeats of a so b is a substring, or -1.
Sample Input: a = "abcd", b = "cdabcdab"
Sample Output: 3
Explanation: "abcd" x 3 contains "cdabcdab".
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
    int repeatedStringMatch(string a, string b) {
        string t = a;
        int cnt = 1;
        while ((int)t.size() < (int)b.size()) {
            t += a;
            cnt++;
        }
        if (t.find(b) != string::npos) return cnt;
        t += a;
        if (t.find(b) != string::npos) return cnt + 1;
        return -1;
    }
};

int main() {
    string a = "abcd";
    string b = "cdabcdab";

    Solution sol;
    auto ans = sol.repeatedStringMatch(a, b);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Repeat until long enough;
at most one extra copy needed.
Time Complexity:
O((n+m) * reps)
Space Complexity:
O(n * reps)
Key Idea:
Ceil(|b|/|a|) or +1, else impossible.
*/
