/*
Problem: Left Right View
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given a binary tree root, return the left view (first node per level) and right view (last node per level).
Sample Input: root = [1,2,3,4,5,6,7]
Sample Output: left [1,2,4], right [1,3,7]
Explanation: BFS edges give each side view.
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
    vector<int> rightSideView(TreeNode* r) {
        vector<int> o;
        if (!r) return o;
        queue<TreeNode*> q;
        q.push(r);
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; i++) {
                auto c = q.front();
                q.pop();
                if (i == n - 1) o.push_back(c->val);
                if (c->left) q.push(c->left);
                if (c->right) q.push(c->right);
            }
        }
        return o;
    }
};
  // Left view: i == 0.

/*
Approach:
Last per level.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
First/last per level.
*/
