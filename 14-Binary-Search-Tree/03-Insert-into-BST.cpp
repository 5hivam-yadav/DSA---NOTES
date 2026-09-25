/*
Problem: Insert Into Binary Search Tree
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search Tree
Statement: Given a BST root and value, insert it as a leaf preserving BST order and return the root.
Sample Input: root = [4,2,7,1,3], val = 5
Sample Output: [4,2,7,1,3,5]
Explanation: 5 goes left of 7.
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
    TreeNode* insertIntoBST(TreeNode* r, int x) {
        if (!r) return new TreeNode(x);
        if (x < r->val) r->left = insertIntoBST(r->left, x);
        else r->right = insertIntoBST(r->right, x);
        return r;
    }
};

/*
Approach:
Descend to null.
Time Complexity:
O(h)
Space Complexity:
O(h)
Key Idea:
Leaf insert.
*/
