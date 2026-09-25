/*
Problem: Next Smaller Element
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Monotonic Stack
Statement: Given an array, return the next smaller element to the right for each position (-1 if none) with a monotonic stack.
Sample Input: a = [4, 5, 2, 10, 8]
Sample Output: [2, 2, -1, 8, -1]
Explanation: Each entry looks right for the first smaller value.
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

vector<int> nse(vector<int>& a) {
    int n = a.size();
    vector<int> r(n, -1);
    vector<int> st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.back()] >= a[i]) st.pop_back();
        if (!st.empty()) r[i] = a[st.back()];
        st.push_back(i);
    }
    return r;
}

int main() {
    vector<int> a = {4, 5, 2, 10, 8};

    auto ans = nse(a);
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Pop >= for smaller.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Strictness matters.
*/
