/*
Problem: Count Complete Nodes
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given a complete binary tree root, count nodes in less than O(n) by comparing left/right heights.
Sample Input: root = [1,2,3,4,5,6]
Sample Output: 6
Explanation: Six nodes are present.
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
    int lh(TreeNode* r) {
        int c = 0;
        while (r) {
            c++;
            r = r->left;
        }
        return c;
    }
    int rh(TreeNode* r) {
        int c = 0;
        while (r) {
            c++;
            r = r->right;
        }
        return c;
    }
    int countNodes(TreeNode* r) {
        if (!r) return 0;
        int l = lh(r), rr = rh(r);
        if (l == rr) return (1 << l) - 1;
        return 1 + countNodes(r->left) + countNodes(r->right);
    }
};

/*
Approach:
Perfect check.
Time Complexity:
O(log^2 n)
Space Complexity:
O(log n)
Key Idea:
2^h - 1 shortcut.
*/
