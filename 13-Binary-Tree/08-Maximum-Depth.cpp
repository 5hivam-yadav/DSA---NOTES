/*
Problem: Maximum Depth
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Tree
Statement: Given a binary tree root, return its maximum depth (nodes along the longest root-to-leaf path).
Sample Input: root = [3, 9, 20, null, null, 15, 7]
Sample Output: 3
Explanation: Path 3 -> 20 -> 15 has 3 nodes.
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
    int maxDepth(TreeNode* r) {
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
