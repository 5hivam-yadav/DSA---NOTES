/*
Problem: Mirror Tree
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given a binary tree root, mirror it (swap left/right at every node) and return the root.
Sample Input: root = [1,2,3]
Sample Output: [1,3,2]
Explanation: Children of 1 swap places.
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
    TreeNode *left, *right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;
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
