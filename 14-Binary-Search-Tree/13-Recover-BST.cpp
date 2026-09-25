/*
Problem: Recover Binary Search Tree
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search Tree
Statement: Given a BST with two nodes swapped, recover it in place (find the two inorder violations, swap back).
Sample Input: root = [1,3,null,null,2]
Sample Output: [3,1,null,null,2]
Explanation: Nodes 1 and 3 swap back to BST order.
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
    TreeNode *a = nullptr, *b = nullptr, *pr = nullptr;
    void f(TreeNode* r) {
        if (!r) return;
        f(r->left);
        if (pr && pr->val > r->val) {
            if (!a) a = pr;
            b = r;
        }
        pr = r;
        f(r->right);
    }
    void recoverTree(TreeNode* r) {
        f(r);
        swap(a->val, b->val);
    }
};
  // Morris O(1) also.

/*
Approach:
Find two inversions.
Time Complexity:
O(n)
Space Complexity:
O(h)
Key Idea:
Inorder violations.
*/
