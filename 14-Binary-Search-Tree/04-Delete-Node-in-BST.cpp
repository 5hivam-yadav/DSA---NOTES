/*
Problem: Delete Node in Binary Search Tree
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Search Tree
Statement: Given a BST root and key, delete the key node (leaf, one child, or
successor swap) and return the root. Sample Input: root = [5,3,6,2,4,null,7],
key = 3 Sample Output: [5,4,6,2,null,null,7] Explanation: Successor 4
replaces 3.
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

class Solution {
  public:
    TreeNode *deleteNode(TreeNode *r, int x) {
        if (!r)
            return nullptr;
        if (x < r->val)
            r->left = deleteNode(r->left, x);
        else if (x > r->val)
            r->right = deleteNode(r->right, x);
        else {
            if (!r->left)
                return r->right;
            if (!r->right)
                return r->left;
            auto s = r->right;
            while (s->left)
                s = s->left;
            r->val = s->val;
            r->right = deleteNode(r->right, s->val);
        }
        return r;
    }
};

/*
Approach:
Successor replace.
Time Complexity:
O(h)
Space Complexity:
O(h)
Key Idea:
Two-child = successor.
*/
