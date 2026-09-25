/*
Problem: Level Order Traversal
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Tree
Statement: Given a binary tree root, return node values level by level from top to bottom.
Sample Input: root = [3, 9, 20, null, null, 15, 7]
Sample Output: [[3], [9, 20], [15, 7]]
Explanation: BFS visits each depth in order.
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
    vector<vector<int>> levelOrder(TreeNode* r) {
        vector<vector<int>> o;
        if (!r) return o;
        queue<TreeNode*> q;
        q.push(r);
        while (!q.empty()) {
            int n = q.size();
            vector<int> lv;
            while (n--) {
                auto c = q.front();
                q.pop();
                lv.push_back(c->val);
                if (c->left) q.push(c->left);
                if (c->right) q.push(c->right);
            }
            o.push_back(lv);
        }
        return o;
    }
};

/*
Approach:
Queue levels.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Size snapshot.
*/
