/*
Problem: Build Binary Search Tree from Preorder
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search Tree
Statement: Given the preorder traversal of a BST, rebuild the BST in O(n) using bounded ranges (bound = ancestor limit).
Sample Input: preorder = [8,5,1,7,10,12]
Sample Output: inorder = [1,5,7,8,10,12]
Explanation: Each value lands in its allowed range, reproducing the BST.
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
    int i = 0;
    TreeNode* f(vector<int>& p, int bound) {
        if (i == (int)p.size() || p[i] > bound) return nullptr;
        auto r = new TreeNode(p[i++]);
        r->left = f(p, r->val);
        r->right = f(p, bound);
        return r;
    }
    TreeNode* bstFromPreorder(vector<int>& p) {
        return f(p, INT_MAX);
    }
};
  // Sort + build O(n log n) also.

/*
Approach:
Bound + index.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Upper-bound split.
*/
