/*
Problem: Diameter of Binary Tree
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given a binary tree root, return its diameter: the number of edges on the longest path between any two nodes.
Sample Input: root = [1, 2, 3, 4, 5]
Sample Output: 3
Explanation: Path 4 -> 2 -> 1 -> 3 uses 3 edges.
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
    int d = 0;
    int h(TreeNode* r) {
        if (!r) return 0;
        int l = h(r->left), rr = h(r->right);
        d = max(d, l + rr);
        return 1 + max(l, rr);
    }
    int diameterOfBinaryTree(TreeNode* r) {
        h(r);
        return d;
    }
};

/*
Approach:
lh+rh at each.
Time Complexity:
O(n)
Space Complexity:
O(h)
Key Idea:
Path via root may win.
*/
