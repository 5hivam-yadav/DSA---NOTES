/*
Problem: Next Greater Element
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Monotonic Stack
Statement: Given an array, return the next greater element to the right for each position (monotonic stack), -1 if none.
Sample Input: a = [4, 5, 2, 25]
Sample Output: [5, 25, 25, -1]
Explanation: Each entry looks right for the first larger value.
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
    vector<int> nextGreaterElement(vector<int>& q, vector<int>& a) {
        unordered_map<int, int> mp;
        vector<int> st;
        for (int i = (int)a.size() - 1; i >= 0; i--) {
            while (!st.empty() && st.back() <= a[i]) st.pop_back();
            mp[a[i]] = st.empty() ? -1 : st.back();
            st.push_back(a[i]);
        }
        vector<int> r;
        for (int x : q) r.push_back(mp[x]);
        return r;
    }
};

/*
Approach:
Dec stack right-to-left.
Time Complexity:
O(n+m)
Space Complexity:
O(n)
Key Idea:
Pop smaller.
*/
