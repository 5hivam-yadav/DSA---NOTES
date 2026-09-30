/*
Problem: Stack Using Arrays
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Stack
Statement: Implement a stack with a fixed array supporting push, pop, top and
size. Sample Input: push 1, push 2, pop, top Sample Output: 2, 1 Explanation:
LIFO: 2 leaves first, 1 is on top next.
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

class ArrStack {
    int a[1000], t = -1;

  public:
    void push(int x) { a[++t] = x; }
    int pop() { return t < 0 ? -1 : a[t--]; }
    int top() { return t < 0 ? -1 : a[t]; }
};

/*
Approach:
top index.
Time Complexity:
O(1)
Space Complexity:
O(N)
Key Idea:
Array + top pointer.
*/
