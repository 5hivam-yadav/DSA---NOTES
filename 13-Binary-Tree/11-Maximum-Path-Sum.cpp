/*
Problem: Maximum Path Sum
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given a binary tree, return the maximum sum over any path (path may
start and end anywhere). Sample Input: root = [-10, 9, 20, null, null, 15, 7]
Sample Output: 42
Explanation: Path 15 -> 20 -> 7 sums to 42.
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
    int b = INT_MIN;
    int f(TreeNode *r) {
        if (!r)
            return 0;
        int l = max(0, f(r->left)), rr = max(0, f(r->right));
        b = max(b, r->val + l + rr);
        return r->val + max(l, rr);
    }
    int maxPathSum(TreeNode *r) {
        f(r);
        return b;
    }
};

/*
Approach:
Clamp negatives to 0.
Time Complexity:
O(n)
Space Complexity:
O(h)
Key Idea:
Any-to-any via root.
*/
