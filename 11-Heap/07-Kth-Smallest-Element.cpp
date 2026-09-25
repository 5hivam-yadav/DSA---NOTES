/*
Problem: Kth Smallest Element
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Heap / Priority Queue
Statement: Given an array and k, return the k-th smallest element using a max-heap of size k.
Sample Input: nums = [7,10,4,3,20,15], k = 3
Sample Output: 7
Explanation: Sorted: 3,4,7,...; 3rd is 7.
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

int kthSmall(vector<int>& a, int k) {
    priority_queue<int> pq;
    for (int x : a) {
        pq.push(x);
        if ((int)pq.size() > k) pq.pop();
    }
    return pq.top();
}

int main() {
    vector<int> nums = {7, 10, 4, 3, 20, 15};
    int k = 3;

    auto ans = kthSmall(nums, k);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Max-heap size k.
Time Complexity:
O(n log k)
Space Complexity:
O(k)
Key Idea:
Mirror of kth largest.
*/
