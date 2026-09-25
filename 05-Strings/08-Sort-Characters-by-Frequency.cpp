/*
Problem: Sort Characters by Frequency
Platform: GFG / Striver A2Z
Problem Number: -
Difficulty: Easy
Pattern: Hashing
Statement: Given a string, reorder characters by decreasing frequency (bucket or heap).
Sample Input: s = "tree"
Sample Output: "eert"
Explanation: e appears twice, then r and t once each.
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
    string frequencySort(string s) {
        int f[128] = {0};
        for (char c : s) f[(unsigned char)c]++;
        vector<pair<int, char>> v;
        for (int i = 0; i < 128; i++) if (f[i]) v.push_back({f[i], (char)i});
        sort(v.begin(), v.end(), greater<pair<int, char>>());
        string r;
        for (auto& p : v) r.append(p.first, p.second);
        return r;
    }
};
  // Bucket O(n) also.

int main() {
    string s = "tree";

    Solution sol;
    auto ans = sol.frequencySort(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Count then sort.
Time Complexity:
O(n + k log k)
Space Complexity:
O(k)
Key Idea:
Freq order.
*/
