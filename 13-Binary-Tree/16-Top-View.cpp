/*
Problem: Top View
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given a binary tree root, return its top view (first node per horizontal distance, level order).
Sample Input: root = [1,2,3,4,5,6,7]
Sample Output: [4,2,1,3,7]
Explanation: Highest node wins each vertical line.
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
vector<int> topView(TreeNode* r) {
    map<int, int> m;
    queue<pair<TreeNode*, int>> q;
    q.push({r, 0});
    while (!q.empty()) {
        auto [n, x] = q.front();
        q.pop();
        if (!m.count(x)) m[x] = n->val;
        if (n->left) q.push({n->left, x - 1});
        if (n->right) q.push({n->right, x + 1});
    }
    vector<int> o;
    for (auto& p : m) o.push_back(p.second);
    return o;
}

/*
Approach:
First per hd.
Time Complexity:
O(n log n)
Space Complexity:
O(n)
Key Idea:
BFS first wins.
*/
