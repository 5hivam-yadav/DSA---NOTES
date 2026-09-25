/*
Problem: Validate Binary Search Tree
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search Tree
Statement: Given a binary tree root, return true if it is a valid BST (left < node < right for every subtree).
Sample Input: root = [2,1,3]
Sample Output: true
Explanation: 1 < 2 < 3 satisfies BST order.
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
    bool f(TreeNode* r, long long lo, long long hi) {
        return !r || (r->val > lo && r->val < hi && f(r->left, lo, r->val) && f(r->right, r->val, hi));
    }
    bool isValidBST(TreeNode* r) {
        return f(r, LLONG_MIN, LLONG_MAX);
    }
};

/*
Approach:
Range tighten.
Time Complexity:
O(n)
Space Complexity:
O(h)
Key Idea:
long long edges.
*/
