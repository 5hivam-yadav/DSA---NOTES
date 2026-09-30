/*
Problem: Max Heap Implementation
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Heap / Priority Queue
Statement: Implement a max-heap with insert, extractMax and peek in O(log n) via
sift up/down on an array. Sample Input: insert 3, insert 1, insert 5, extractMax
Sample Output: 5
Explanation: 5 is the largest and leaves first.
*/
#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class MaxHeap {
    vector<int> h;
    void up(int i) {
        while (i > 0 && h[(i - 1) / 2] < h[i]) {
            swap(h[(i - 1) / 2], h[i]);
            i = (i - 1) / 2;
        }
    }
    void down(int i) {
        int n = h.size();
        while (1) {
            int l = 2 * i + 1, r = 2 * i + 2, s = i;
            if (l < n && h[l] > h[s])
                s = l;
            if (r < n && h[r] > h[s])
                s = r;
            if (s == i)
                break;
            swap(h[i], h[s]);
            i = s;
        }
    }

  public:
    void push(int x) {
        h.push_back(x);
        up(h.size() - 1);
    }
    int top() { return h[0]; }
    void pop() {
        h[0] = h.back();
        h.pop_back();
        if (!h.empty())
            down(0);
    }
};

/*
Approach:
Mirror of min.
Time Complexity:
O(log n)
Space Complexity:
O(n)
Key Idea:
Compare flip.
*/
