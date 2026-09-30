/*
Problem: Rearrange by Sign
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Arrays
Statement: Given an array with equal positive and negative numbers, rearrange it
alternating sign starting positive, preserving order. Sample Input: a = [3, 1,
-2, -5, 2, -4] Sample Output: [3, -2, 1, -5, 2, -4] Explanation: Positives take
even slots, negatives odd slots.
*/
#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
  public:
    vector<int> rearrangeArray(vector<int> &a) {
        int n = a.size();
        vector<int> r(n);
        int p = 0, q = 1;
        for (int x : a) {
            if (x > 0) {
                r[p] = x;
                p += 2;
            } else {
                r[q] = x;
                q += 2;
            }
        }
        return r;
    }
};

int main() {
    vector<int> a = {3, 1, -2, -5, 2, -4};

    Solution sol;
    auto ans = sol.rearrangeArray(a);
    for (int i = 0; i < (int)ans.size(); i++)
        cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Even=pos odd=neg.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Two writers.
*/
