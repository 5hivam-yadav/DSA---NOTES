/*
Problem: Children Sum Property
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given a binary tree root, enforce children-sum (node value = sum of children) top-down, then return the root.
Sample Input: root = [2,35,10,2,3,5,2]
Sample Output: adjusted tree satisfies property
Explanation: Values are pushed down so parents equal child sums.
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
void prop(TreeNode* r) {
    if (!r) return;
    int c = 0;
    if (r->left) c += r->left->val;
    if (r->right) c += r->right->val;
    if (c >= r->val) r->val = c;
    else {
        if (r->left) r->left->val = r->val;
        else if (r->right) r->right->val = r->val;
    }
    prop(r->left);
    prop(r->right);
    int t = 0;
    if (r->left) t += r->left->val;
    if (r->right) t += r->right->val;
    if (r->left || r->right) r->val = t;
}

/*
Approach:
Push down then fix up.
Time Complexity:
O(n)
Space Complexity:
O(h)
Key Idea:
Two-phase adjust.
*/
