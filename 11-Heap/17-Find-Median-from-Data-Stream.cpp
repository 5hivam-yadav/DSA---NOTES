/*
Problem: Find Median from Data Stream
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Heap / Priority Queue
Statement: Support addNum and findMedian over a stream using a max-heap for the lower half and min-heap for the upper half.
Sample Input: add 1, add 2, median, add 3, median
Sample Output: 1.5, 2.0
Explanation: Sorted [1,2] medians 1.5; [1,2,3] medians 2.
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

class MedianFinder {
    priority_queue<int> lo;
    priority_queue<int, vector<int>, greater<int>> hi;
public:
    void addNum(int x) {
        lo.push(x);
        hi.push(lo.top());
        lo.pop();
        if (lo.size() < hi.size()) {
            lo.push(hi.top());
            hi.pop();
        }
    }
    double findMedian() {
        return lo.size() > hi.size() ? lo.top() : (lo.top() + hi.top()) / 2.0;
    }
};

/*
Approach:
Balance halves.
Time Complexity:
O(log n)
Space Complexity:
O(n)
Key Idea:
Max-left/min-right.
*/
