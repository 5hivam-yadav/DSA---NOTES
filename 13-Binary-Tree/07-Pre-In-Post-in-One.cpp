/*
Problem: Pre in Post in One
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Tree
Statement: Given a binary tree root, return preorder, inorder and postorder traversals in a single stack pass.
Sample Input: root = [1,2,3]
Sample Output: pre [1,2,3], in [2,1,3], post [2,3,1]
Explanation: One traversal fills all three orders.
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

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};
  // Stack of (node, state): 1=pre, 2=in, 3=post; push children with state transitions.

/*
Approach:
State machine.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
One pass three orders.
*/
