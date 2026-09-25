/*
Problem: LCA Binary Tree
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given a binary tree and nodes p and q, return their lowest common ancestor.
Sample Input: root = [3, 5, 1, 6, 2, 0, 8], p = 5, q = 1
Sample Output: 3
Explanation: Node 3 is the deepest node above both.
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
        if (!r || r == p || r == q) return r;
        auto L = lowestCommonAncestor(r->left, p, q), R = lowestCommonAncestor(r->right, p, q);
        return L && R ? r : (L ? L : R);
    }
};

/*
Approach:
Split = root.
Time Complexity:
O(n)
Space Complexity:
O(h)
Key Idea:
First split up.
*/
