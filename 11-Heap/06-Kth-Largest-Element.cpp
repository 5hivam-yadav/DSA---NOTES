/*
Problem: Kth Largest Element
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Heap / Priority Queue
Statement: Given an array and k, return the k-th largest element using a min-heap of size k.
Sample Input: nums = [3,2,1,5,6,4], k = 2
Sample Output: 5
Explanation: Sorted descending: 6, 5, ...; 2nd is 5.
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
    int findKthLargest(vector<int>& a, int k) {
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int x : a) {
            pq.push(x);
            if ((int)pq.size() > k) pq.pop();
        }
        return pq.top();
    }
};
  // Brute sort O(n log n); quickselect avg O(n).

int main() {
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    int k = 2;

    Solution sol;
    auto ans = sol.findKthLargest(nums, k);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Min-heap size k.
Time Complexity:
O(n log k)
Space Complexity:
O(k)
Key Idea:
Top = kth.
*/
