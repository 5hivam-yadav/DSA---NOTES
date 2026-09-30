/*
Problem: Tree from in Level
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given inorder and level-order arrays, rebuild the binary tree (root =
first level element present in segment). Sample Input: inorder =
[4,2,5,1,6,3,7], level = [1,2,3,4,5,6,7] Sample Output: [1,2,3,4,5,6,7]
Explanation: Balanced tree is reconstructed.
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
// Level head = root; inorder split; filter level arrays for children.

/*
Approach:
Level root pick.
Time Complexity:
O(n^2)
Space Complexity:
O(n)
Key Idea:
Level preserves BFS order.
*/
