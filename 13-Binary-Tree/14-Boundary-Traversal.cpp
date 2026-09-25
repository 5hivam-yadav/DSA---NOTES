/*
Problem: Boundary Traversal
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given a binary tree root, return left boundary + leaves + reversed right boundary.
Sample Input: root = [1,2,3,4,5,6,7]
Sample Output: [1,2,4,5,6,7,3]
Explanation: Boundaries plus leaves in order.
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
bool leaf(TreeNode* r) {
    return r && !r->left && !r->right;
}
void leftB(TreeNode* r, vector<int>& o) {
    while (r) {
        if (!leaf(r)) o.push_back(r->val);
        r = r->left ? r->left : r->right;
    }
}
  // left + leaves + right-reverse; skip leaves in sides, skip root dup.

/*
Approach:
Three parts.
Time Complexity:
O(n)
Space Complexity:
O(h)
Key Idea:
No double leaves.
*/
