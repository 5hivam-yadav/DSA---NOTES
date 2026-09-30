/*
Problem: Burn Tree Min Time
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given a binary tree root and start node, return minutes to burn the
whole tree (spread to parent/children per minute). Sample Input: root =
[1,2,3,4,5], start = 2 Sample Output: 3 Explanation: Fire needs 3 minutes to
reach node 3.
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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
// Parent map like distance-K; BFS from target; time = farthest level.

/*
Approach:
Spread levels.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Max distance from target.
*/
