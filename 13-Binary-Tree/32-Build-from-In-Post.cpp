/*
Problem: Build from in Post
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given inorder and postorder arrays (unique values), rebuild the binary tree (root = postorder tail).
Sample Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
Sample Output: [3,9,20,null,null,15,7]
Explanation: Same tree as the pre/in sample.
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
    TreeNode* f(vector<int>& ino, int il, int ir, vector<int>& post, int pl, int pr, unordered_map<int, int>& m) {
        if (il > ir) return nullptr;
        auto r = new TreeNode(post[pr]);
        int k = m[post[pr]], L = k - il;
        r->left = f(ino, il, k - 1, post, pl, pl + L - 1, m);
        r->right = f(ino, k + 1, ir, post, pl + L, pr - 1, m);
        return r;
    }
    TreeNode* buildTree(vector<int>& ino, vector<int>& post) {
        unordered_map<int, int> m;
        for (int i = 0; i < (int)ino.size(); i++) m[ino[i]] = i;
        return f(ino, 0, ino.size() - 1, post, 0, post.size() - 1, m);
    }
};

/*
Approach:
Post root at end.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Mirror of pre/in.
*/
