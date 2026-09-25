/*
Problem: Build from Pre in
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given preorder and inorder arrays (unique values), rebuild the binary tree (root = preorder head, split inorder).
Sample Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Sample Output: [3,9,20,null,null,15,7]
Explanation: 9 left of 3; 15,7 under 20.
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
    TreeNode* f(vector<int>& pre, int pl, int pr, vector<int>& ino, int il, int ir, unordered_map<int, int>& m) {
        if (pl > pr) return nullptr;
        auto r = new TreeNode(pre[pl]);
        int k = m[pre[pl]], L = k - il;
        r->left = f(pre, pl + 1, pl + L, ino, il, k - 1, m);
        r->right = f(pre, pl + L + 1, pr, ino, k + 1, ir, m);
        return r;
    }
    TreeNode* buildTree(vector<int>& pre, vector<int>& ino) {
        unordered_map<int, int> m;
        for (int i = 0; i < (int)ino.size(); i++) m[ino[i]] = i;
        return f(pre, 0, pre.size() - 1, ino, 0, ino.size() - 1, m);
    }
};

/*
Approach:
Root + split map.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Pre root, in split.
*/
