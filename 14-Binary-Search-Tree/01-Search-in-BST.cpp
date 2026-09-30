/*
Problem: Search in Binary Search Tree
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search Tree
Statement: Given a BST root and value, return the node with that value or null
(go left if smaller, right if larger). Sample Input: root = [4,2,7,1,3], val = 2
Sample Output: [2,1,3]
Explanation: Subtree rooted at 2 is returned.
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
    TreeNode *searchBST(TreeNode *r, int x) {
        while (r) {
            if (x == r->val)
                return r;
            r = (x < r->val) ? r->left : r->right;
        }
        return nullptr;
    }
};

/*
Approach:
Go left/right.
Time Complexity:
O(h)
Space Complexity:
O(1)
Key Idea:
BST order.
*/
