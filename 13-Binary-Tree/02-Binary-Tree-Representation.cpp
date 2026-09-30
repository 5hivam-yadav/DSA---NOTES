/*
Problem: Binary Tree Representation
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given values, build a small binary tree (nodes with left/right links)
as a representation demo. Sample Input: values = [1,2,3] Sample Output: root 1
with left 2, right 3 Explanation: Node 1 links to children 2 and 3.
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
TreeNode *buildExample() {
    TreeNode *n = new TreeNode(1);
    n->left = new TreeNode(2);
    n->right = new TreeNode(3);
    return n;
}

/*
Approach:
Node struct + links.
Time Complexity:
O(1)
Space Complexity:
O(1)
Key Idea:
left/right pointers.
*/
