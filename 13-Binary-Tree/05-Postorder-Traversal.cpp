/*
Problem: Postorder Traversal
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Tree
Statement: Given a binary tree root, return its postorder traversal (left,
right, node). Sample Input: root = [1,null,2,3] Sample Output: [3,2,1]
Explanation: Children come before their parent.
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
    void f(TreeNode *r, vector<int> &o) {
        if (!r)
            return;
        f(r->left, o);
        f(r->right, o);
        o.push_back(r->val);
    }
    vector<int> postorderTraversal(TreeNode *r) {
        vector<int> o;
        f(r, o);
        return o;
    }
};

/*
Approach:
Left, right, node.
Time Complexity:
O(n)
Space Complexity:
O(h)
Key Idea:
Children first.
*/
