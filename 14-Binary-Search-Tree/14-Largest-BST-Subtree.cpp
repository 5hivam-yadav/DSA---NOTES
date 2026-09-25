/*
Problem: Largest Binary Search Tree Subtree
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search Tree
Statement: Given a binary tree root, return the size of the largest BST subtree (post-order validity + sizes).
Sample Input: root = [10,5,15,1,8,null,7]
Sample Output: 3
Explanation: Subtree [5,1,8] is the largest BST.
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
    struct T {
        bool ok;
        int sz, mn, mx;
    };
    T f(TreeNode* r) {
        if (!r) return { true, 0, INT_MAX, INT_MIN};
        auto L = f(r->left), R = f(r->right);
        if (L.ok && R.ok && r->val > L.mx && r->val < R.mn) return { true, L.sz + R.sz + 1, min(r->val, L.mn), max(r->val, R.mx)};
        return { false, max(L.sz, R.sz), 0, 0};
    }
    int largestBSTSubtree(TreeNode* r) {
        return f(r).sz;
    }
};

/*
Approach:
Return size/min/max.
Time Complexity:
O(n)
Space Complexity:
O(h)
Key Idea:
Bottom-up info.
*/
