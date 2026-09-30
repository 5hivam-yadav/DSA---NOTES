/*
Problem: Pre in Post in One
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Tree
Statement: Given a binary tree root, return preorder, inorder and postorder
traversals in a single stack pass. Sample Input: root = [1,2,3] Sample Output:
pre [1,2,3], in [2,1,3], post [2,3,1] Explanation: One traversal fills all three
orders.
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
// Stack of (node, state): 1=pre, 2=in, 3=post; push children with state
// transitions.

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
