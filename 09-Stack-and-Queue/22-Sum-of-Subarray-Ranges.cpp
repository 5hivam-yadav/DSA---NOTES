/*
Problem: Sum of Subarray Ranges
Platform: LeetCode
Problem Number: -
Difficulty: Medium
Pattern: Monotonic Stack
Statement: Given an array, return the sum over subarrays of (max - min) = sum of maximums minus sum of minimums.
Sample Input: nums = [1, 2, 3]
Sample Output: 4
Explanation: Ranges: [1]=0,[2]=0,[3]=0,[1,2]=1,[2,3]=1,[1,2,3]=2; total 4.
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
    long long subMin(vector<int>& a) {
        int n = a.size();
        vector<int> L(n), R(n);
        vector<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && a[st.back()] > a[i]) st.pop_back();
            L[i] = st.empty() ? i + 1 : i - st.back();
            st.push_back(i);
        }
        st.clear();
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && a[st.back()] >= a[i]) st.pop_back();
            R[i] = st.empty() ? n - i : st.back() - i;
            st.push_back(i);
        }
        long long s = 0;
        for (int i = 0; i < n; i++) s += 1LL * a[i] * L[i] * R[i];
        return s;
    }
    long long subMax(vector<int>& a) {
        int n = a.size();
        vector<int> L(n), R(n);
        vector<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && a[st.back()] < a[i]) st.pop_back();
            L[i] = st.empty() ? i + 1 : i - st.back();
            st.push_back(i);
        }
        st.clear();
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && a[st.back()] <= a[i]) st.pop_back();
            R[i] = st.empty() ? n - i : st.back() - i;
            st.push_back(i);
        }
        long long s = 0;
        for (int i = 0; i < n; i++) s += 1LL * a[i] * L[i] * R[i];
        return s;
    }
    long long subArrayRanges(vector<int>& a) {
        return subMax(a) - subMin(a);
    }
};

int main() {
    vector<int> nums = {1, 2, 3};

    Solution sol;
    auto ans = sol.subMin(nums);
    cout << ans << endl;
    return 0;
}

/*
Approach:
max-sum minus min-sum.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Reuse min/max contrib.
*/
