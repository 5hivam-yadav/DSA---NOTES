/*
Problem: LCA in Binary Search Tree
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search Tree
Statement: Given a BST root and nodes p, q, return their lowest common ancestor (split point where p/q diverge).
Sample Input: root = [6,2,8,0,4,7,9], p = 2, q = 8
Sample Output: 6
Explanation: 2 goes left, 8 goes right from 6.
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
    TreeNode* lowestCommonAncestor(TreeNode* r, TreeNode* p, TreeNode* q) {
        while (r) {
            if (p->val < r->val && q->val < r->val) r = r->left;
            else if (p->val > r->val && q->val > r->val) r = r->right;
            else return r;
        }
        return nullptr;
    }
};

/*
Approach:
Split by value.
Time Complexity:
O(h)
Space Complexity:
O(1)
Key Idea:
BST LCA walk.
*/
