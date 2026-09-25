/*
Problem: Tree from in Level
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given inorder and level-order arrays, rebuild the binary tree (root = first level element present in segment).
Sample Input: inorder = [4,2,5,1,6,3,7], level = [1,2,3,4,5,6,7]
Sample Output: [1,2,3,4,5,6,7]
Explanation: Balanced tree is reconstructed.
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
