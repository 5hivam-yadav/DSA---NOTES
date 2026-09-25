/*
Problem: Largest Rectangle Histogram
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Monotonic Stack
Statement: Given bar heights, return the largest rectangle area (previous/next smaller with a monotonic stack).
Sample Input: heights = [2, 1, 5, 6, 2, 3]
Sample Output: 10
Explanation: Bars [5, 6] with height 5 span width 2.
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
    int largestRectangleArea(vector<int>& h) {
        h.push_back(0);
        vector<int> st;
        int b = 0;
        for (int i = 0; i < (int)h.size(); i++) {
            while (!st.empty() && h[st.back()] > h[i]) {
                int hh = h[st.back()];
                st.pop_back();
                int w = st.empty() ? i : i - st.back() - 1;
                b = max(b, hh * w);
            }
            st.push_back(i);
        }
        return b;
    }
};

int main() {
    vector<int> heights = {2, 1, 5, 6, 2, 3};

    Solution sol;
    auto ans = sol.largestRectangleArea(heights);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Pop taller, width span.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Sentinel flush.
*/
