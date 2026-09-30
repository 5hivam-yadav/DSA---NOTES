/*
Problem: Maximum Depth
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Tree
Statement: Given a binary tree root, return its maximum depth (nodes along the
longest root-to-leaf path). Sample Input: root = [3, 9, 20, null, null, 15, 7]
Sample Output: 3
Explanation: Path 3 -> 20 -> 15 has 3 nodes.
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
    int maxDepth(TreeNode *r) {
        return r ? 1 + max(maxDepth(r->left), maxDepth(r->right)) : 0;
    }
};

/*
Approach:
1+max kids.
Time Complexity:
O(n)
Space Complexity:
O(h)
Key Idea:
Height nodes.
*/
