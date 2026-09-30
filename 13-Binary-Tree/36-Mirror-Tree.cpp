/*
Problem: Mirror Tree
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given a binary tree root, mirror it (swap left/right at every node)
and return the root. Sample Input: root = [1,2,3] Sample Output: [1,3,2]
Explanation: Children of 1 swap places.
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
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
  public:
    TreeNode *invertTree(TreeNode *root) {
        if (!root)
            return nullptr;
        swap(root->left, root->right);
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};

/*
Approach:
Swap children recursively (preorder).
Time Complexity:
O(n)
Space Complexity:
O(h)
Key Idea:
Mirror = swap + recurse.
*/
