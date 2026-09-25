/*
Problem: Zigzag Traversal
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given a binary tree root, return zigzag level order alternating direction per level.
Sample Input: root = [3,9,20,null,null,15,7]
Sample Output: [[3],[20,9],[15,7]]
Explanation: Level 1 runs right-to-left.
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* r) {
        vector<vector<int>> o;
        if (!r) return o;
        queue<TreeNode*> q;
        q.push(r);
        bool L = true;
        while (!q.empty()) {
            int n = q.size();
            vector<int> lv(n);
            for (int i = 0; i < n; i++) {
                auto c = q.front();
                q.pop();
                lv[L ? i : n - 1 - i] = c->val;
                if (c->left) q.push(c->left);
                if (c->right) q.push(c->right);
            }
            o.push_back(lv);
            L = !L;
        }
        return o;
    }
};

/*
Approach:
Alternate write index.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Level reverse flag.
*/
