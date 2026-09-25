/*
Problem: Largest Rectangle Done
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Monotonic Stack
Statement: Given bar heights, return the largest rectangle area (previous/next smaller with a monotonic stack).
Sample Input: heights = [2,1,5,6,2,3]
Sample Output: 10
Explanation: Bars [5,6] with height 5 span width 2.
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

  // See 54 for stack solution; DP boundaries L/R smaller also O(n).

/*
Approach:
Boundaries.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Same as 54 core.
*/
