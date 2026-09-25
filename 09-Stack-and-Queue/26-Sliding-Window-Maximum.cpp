/*
Problem: Sliding Window Maximum
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Queue / Deque
Statement: Given an array and k, return the maximum of every window of size k with a decreasing deque.
Sample Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Sample Output: [3,3,5,5,6,7]
Explanation: Each window contributes its maximum.
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
    vector<int> maxSlidingWindow(vector<int>& a, int k) {
        deque<int> dq;
        vector<int> r;
        for (int i = 0; i < (int)a.size(); i++) {
            while (!dq.empty() && dq.front() <= i - k) dq.pop_front();
            while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
            dq.push_back(i);
            if (i >= k - 1) r.push_back(a[dq.front()]);
        }
        return r;
    }
};

int main() {
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;

    Solution sol;
    auto ans = sol.maxSlidingWindow(nums, k);
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Dec deque of idx.
Time Complexity:
O(n)
Space Complexity:
O(k)
Key Idea:
Front = max.
*/
