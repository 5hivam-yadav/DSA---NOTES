/*
Problem: Kth Largest in Stream
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Heap / Priority Queue
Statement: Design a class with add(val) returning the k-th largest seen so far (min-heap of size k).
Sample Input: k = 3, add 4, add 5, add 8, add 2
Sample Output: 4, 5, 5, 4
Explanation: Heap of top 3 yields the k-th each time.
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

class KthLargest {
    int k;
    priority_queue<int, vector<int>, greater<int>> pq;
public:
    KthLargest(int kk, vector<int>& a): k(kk) {
        for (int x : a) {
            pq.push(x);
            if ((int)pq.size() > k) pq.pop();
        }
    }
    int add(int x) {
        pq.push(x);
        if ((int)pq.size() > k) pq.pop();
        return pq.top();
    }
};

/*
Approach:
Keep size-k heap.
Time Complexity:
O(log k)
Space Complexity:
O(k)
Key Idea:
Streaming top-k.
*/
