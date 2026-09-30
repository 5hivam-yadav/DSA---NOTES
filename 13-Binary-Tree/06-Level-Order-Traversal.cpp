/*
Problem: Level Order Traversal
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Tree
Statement: Given a binary tree root, return node values level by level from top
to bottom. Sample Input: root = [3, 9, 20, null, null, 15, 7] Sample Output:
[[3], [9, 20], [15, 7]] Explanation: BFS visits each depth in order.
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
    vector<vector<int>> levelOrder(TreeNode *r) {
        vector<vector<int>> o;
        if (!r)
            return o;
        queue<TreeNode *> q;
        q.push(r);
        while (!q.empty()) {
            int n = q.size();
            vector<int> lv;
            while (n--) {
                auto c = q.front();
                q.pop();
                lv.push_back(c->val);
                if (c->left)
                    q.push(c->left);
                if (c->right)
                    q.push(c->right);
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
