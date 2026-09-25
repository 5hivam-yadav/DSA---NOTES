/*
Problem: Nodes at Distance K
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given a binary tree root, target and k, return all nodes k edges away (parent links + BFS from target).
Sample Input: root = [3,5,1,6,2,0,8], target = 5, k = 2
Sample Output: [7,4,1]
Explanation: Nodes 7, 4 (children path) and 1 (via root) qualify.
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
    void parent(TreeNode* r, unordered_map<TreeNode*, TreeNode*>& p) {
        if (!r) return;
        if (r->left) {
            p[r->left] = r;
            parent(r->left, p);
        }
        if (r->right) {
            p[r->right] = r;
            parent(r->right, p);
        }
    }
    vector<int> distanceK(TreeNode* r, TreeNode* t, int k) {
        unordered_map<TreeNode*, TreeNode*> p;
        parent(r, p);
        unordered_set<TreeNode*> v;
        queue<TreeNode*> q;
        q.push(t);
        v.insert(t);
        while (!q.empty() && k--) {
            int n = q.size();
            while (n--) {
                auto c = q.front();
                q.pop();
                if (c->left && !v.count(c->left)) {
                    v.insert(c->left);
                    q.push(c->left);
                }
                if (c->right && !v.count(c->right)) {
                    v.insert(c->right);
                    q.push(c->right);
                }
                if (p.count(c) && !v.count(p[c])) {
                    v.insert(p[c]);
                    q.push(p[c]);
                }
            }
        }
        vector<int> o;
        while (!q.empty()) {
            o.push_back(q.front()->val);
            q.pop();
        }
        return o;
    }
};

/*
Approach:
Parent map + BFS.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Tree as graph.
*/
