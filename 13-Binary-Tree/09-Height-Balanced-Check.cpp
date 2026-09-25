/*
Problem: Height Balanced Check
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given a binary tree root, return true if it is height-balanced (every subtree heights differ by at most 1).
Sample Input: root = [3,9,20,null,null,15,7]
Sample Output: true
Explanation: All subtrees differ by at most one level.
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
    int h(TreeNode* r) {
        if (!r) return 0;
        int l = h(r->left);
        if (l < 0) return -1;
        int rr = h(r->right);
        if (rr < 0) return -1;
        if (abs(l - rr) > 1) return -1;
        return 1 + max(l, rr);
    }
    bool isBalanced(TreeNode* r) {
        return h(r) >= 0;
    }
};

/*
Approach:
-1 = bad.
Time Complexity:
O(n)
Space Complexity:
O(h)
Key Idea:
One pass height.
*/
