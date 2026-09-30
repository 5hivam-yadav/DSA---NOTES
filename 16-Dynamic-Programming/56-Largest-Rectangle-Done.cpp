/*
Problem: Largest Rectangle Done
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Monotonic Stack
Statement: Given bar heights, return the largest rectangle area (previous/next
smaller with a monotonic stack). Sample Input: heights = [2,1,5,6,2,3] Sample
Output: 10 Explanation: Bars [5,6] with height 5 span width 2.
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
