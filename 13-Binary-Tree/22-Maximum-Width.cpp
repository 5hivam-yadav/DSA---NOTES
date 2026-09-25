/*
Problem: Maximum Width
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given a binary tree root, return its maximum width counting null gaps (BFS with position indices).
Sample Input: root = [1,3,2,5,3,null,9]
Sample Output: 4
Explanation: Level [5,3,null,9] spans 4 positions.
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
    int widthOfBinaryTree(TreeNode* r) {
        unsigned long long b = 0;
        queue<pair<TreeNode*, unsigned long long>> q;
        q.push({r, 0});
        while (!q.empty()) {
            int n = q.size();
            unsigned long long l = q.front().second, rr = l;
            while (n--) {
                auto [nd, idx] = q.front();
                q.pop();
                rr = idx;
                if (nd->left) q.push({nd->left, 2 * idx + 1});
                if (nd->right) q.push({nd->right, 2 * idx + 2});
            }
            b = max(b, rr - l + 1);
        }
        return (int)b;
    }
};
  // Normalize per level to avoid overflow.

/*
Approach:
Index heap-style.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Width = last-first+1.
*/
