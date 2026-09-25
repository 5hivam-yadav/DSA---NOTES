/*
Problem: Introduction to Priority Queue
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Heap / Priority Queue
Statement: Introduce heap basics: push values into a min-heap (and max-heap) and pop the top element.
Sample Input: values = [5,1,4]
Sample Output: min-top 1, max-top 5
Explanation: Heaps expose the extreme element first.
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

priority_queue<int> mx;
priority_queue<int, vector<int>, greater<int>> mn;
  // push O(log n), top O(1), pop O(log n).

/*
Approach:
Max vs min heap.
Time Complexity:
O(log n)
Space Complexity:
O(n)
Key Idea:
Heap = top-first structure.
*/
