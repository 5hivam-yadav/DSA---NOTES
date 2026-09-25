/*
Problem: Symmetric Tree
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given a binary tree root, return true if it mirrors itself around the centre.
Sample Input: root = [1, 2, 2, 3, 4, 4, 3]
Sample Output: true
Explanation: Left and right subtrees are mirror images.
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

class Solution {
public:
    bool f(TreeNode* a, TreeNode* b) {
        if (!a || !b) return a == b;
        return a->val == b->val && f(a->left, b->right) && f(a->right, b->left);
    }
    bool isSymmetric(TreeNode* r) {
        return !r || f(r->left, r->right);
    }
};

/*
Approach:
Mirror pair.
Time Complexity:
O(n)
Space Complexity:
O(h)
Key Idea:
Cross recursion.
*/
