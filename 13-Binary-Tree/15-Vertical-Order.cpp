/*
Problem: Vertical Order
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given a binary tree root, return vertical order grouped by column then row (values sorted on ties).
Sample Input: root = [3,9,20,null,null,15,7]
Sample Output: [[9],[3,15],[20],[7]]
Explanation: Columns left to right hold those nodes.
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
    vector<vector<int>> verticalTraversal(TreeNode* r) {
        map<int, map<int, multiset<int>>> m;
        queue<tuple<TreeNode*, int, int>> q;
        q.push({r, 0, 0});
        while (!q.empty()) {
            auto [n, x, y] = q.front();
            q.pop();
            m[x][y].insert(n->val);
            if (n->left) q.push({n->left, x - 1, y + 1});
            if (n->right) q.push({n->right, x + 1, y + 1});
        }
        vector<vector<int>> o;
        for (auto& px : m) {
            vector<int> c;
            for (auto& py : px.second) for (int v : py.second) c.push_back(v);
            o.push_back(c);
        }
        return o;
    }
};

/*
Approach:
hd + level + multiset.
Time Complexity:
O(n log n)
Space Complexity:
O(n)
Key Idea:
Sort per coordinate.
*/
