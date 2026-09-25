/*
Problem: Maximal Rectangle
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Monotonic Stack
Statement: Given a binary matrix, return the largest all-1 rectangle area (histogram per row + stack).
Sample Input: matrix = [["1","0"],["1","0"],["1","1"]]
Sample Output: 4
Explanation: Bottom two rows form a 2x2 block.
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
    int hist(vector<int>& h) {
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
        h.pop_back();
        return b;
    }
    int maximalRectangle(vector<vector<char>>& m) {
        if (m.empty()) return 0;
        int C = m[0].size(), b = 0;
        vector<int> h(C, 0);
        for (auto& r : m) {
            for (int j = 0; j < C; j++) h[j] = (r[j] == '1' ? h[j] + 1 : 0);
            b = max(b, hist(h));
        }
        return b;
    }
};

/*
Approach:
Histogram per row.
Time Complexity:
O(RC)
Space Complexity:
O(C)
Key Idea:
Stack per layer.
*/
