/*
Problem: Sum of Subarray Minimums
Platform: LeetCode
Problem Number: -
Difficulty: Hard
Pattern: Monotonic Stack
Statement: Given an array, return the sum of the minimum of every subarray modulo 1e9+7 (previous/next smaller contributions).
Sample Input: arr = [3, 1, 2, 4]
Sample Output: 17
Explanation: Minima of all 10 subarrays sum to 17.
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
    const int M = 1000000007;
    int sumSubarrayMins(vector<int>& a) {
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
        long long ans = 0;
        for (int i = 0; i < n; i++) ans = (ans + 1LL * a[i] * L[i] * R[i]) % M;
        return (int)ans;
    }
};

int main() {
    vector<int> arr = {3, 1, 2, 4};

    Solution sol;
    auto ans = sol.sumSubarrayMins(arr);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Prev-less + next-less-eq.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Contribution counting.
*/
