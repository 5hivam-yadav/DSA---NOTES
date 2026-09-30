/*
Problem: Next Greater Element II
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Monotonic Stack
Statement: Given a circular array, return the next greater element for each
position (-1 if none) with a monotonic stack over 2n. Sample Input: a = [1, 2,
1] Sample Output: [2, -1, 2] Explanation: Wrap-around finds 2 for the last 1.
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
    vector<int> nextGreaterElements(vector<int> &a) {
        int n = a.size();
        vector<int> r(n, -1);
        vector<int> st;
        for (int i = 2 * n - 1; i >= 0; i--) {
            while (!st.empty() && st.back() <= a[i % n])
                st.pop_back();
            if (i < n)
                r[i] = st.empty() ? -1 : st.back();
            st.push_back(a[i % n]);
        }
        return r;
    }
};

int main() {
    vector<int> a = {1, 2, 1};

    Solution sol;
    auto ans = sol.nextGreaterElements(a);
    for (int i = 0; i < (int)ans.size(); i++)
        cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
2n virtual loop.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Circular double pass.
*/
