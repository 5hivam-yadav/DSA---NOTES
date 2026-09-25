/*
Problem: Min Heap Implementation
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Heap / Priority Queue
Statement: Implement a min-heap with insert, extractMin and peek in O(log n) via sift up/down on an array.
Sample Input: insert 3, insert 1, insert 5, extractMin
Sample Output: 1
Explanation: 1 is the smallest and leaves first.
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

class MinHeap {
    vector<int> h;
    void up(int i) {
        while (i > 0 && h[(i-1)/2] > h[i]) {
            swap(h[(i-1)/2], h[i]);
            i = (i-1)/2;
        }
    }
    void down(int i) {
        int n = h.size();
        while (1) {
            int l = 2*i+1, r = 2*i+2, s = i;
            if (l < n && h[l] < h[s]) s = l;
            if (r < n && h[r] < h[s]) s = r;
            if (s == i) break;
            swap(h[i], h[s]);
            i = s;
        }
    }
public:
    void push(int x) {
        h.push_back(x);
        up(h.size()-1);
    }
    int top() {
        return h[0];
    }
    void pop() {
        h[0] = h.back();
        h.pop_back();
        if (!h.empty()) down(0);
    }
};

/*
Approach:
Sift up/down.
Time Complexity:
O(log n)
Space Complexity:
O(n)
Key Idea:
Array heap.
*/
