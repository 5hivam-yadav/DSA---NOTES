/*
Problem: Fruits Into Baskets
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Sliding Window
Statement: Given tree types, pick the longest subarray with at most 2 distinct values (sliding window).
Sample Input: fruits = [1,2,1]
Sample Output: 3
Explanation: The whole array uses only {1,2}.
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
    int totalFruit(vector<int>& f) {
        unordered_map<int, int> c;
        int l = 0, b = 0;
        for (int r = 0; r < (int)f.size(); r++) {
            c[f[r]]++;
            while (c.size() > 2) {
                if (--c[f[l]] == 0) c.erase(f[l]);
                l++;
            }
            b = max(b, r - l + 1);
        }
        return b;
    }
};

int main() {
    vector<int> fruits = {1, 2, 1};

    Solution sol;
    auto ans = sol.totalFruit(fruits);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Distinct <= 2.
Time Complexity:
O(n) avg
Space Complexity:
O(1)
Key Idea:
At-most-2 window.
*/
