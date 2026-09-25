/*
Problem: Postorder from in Pre
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Tree
Statement: Given inorder and preorder arrays, return the postorder traversal without rebuilding links (split by root).
Sample Input: inorder = [4,2,5,1,6,3,7], preorder = [1,2,4,5,3,6,7]
Sample Output: [4,5,2,6,7,3,1]
Explanation: Postorder of the same balanced tree.
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
  // Pre root + inorder split gives left/right sizes; recurse then emit root.

/*
Approach:
Derive sizes.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Print post without build.
*/
