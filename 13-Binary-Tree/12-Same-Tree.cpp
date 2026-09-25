/*
Problem: Same Tree
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given two binary trees, return true if they are structurally identical with equal values.
Sample Input: p = [1, 2, 3], q = [1, 2, 3]
Sample Output: true
Explanation: Both position and value match everywhere.
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
    bool isSameTree(TreeNode* a, TreeNode* b) {
        if (!a || !b) return a == b;
        return a->val == b->val && isSameTree(a->left, b->left) && isSameTree(a->right, b->right);
    }
};

/*
Approach:
Structure + value.
Time Complexity:
O(n)
Space Complexity:
O(h)
Key Idea:
Pair recursion.
*/
