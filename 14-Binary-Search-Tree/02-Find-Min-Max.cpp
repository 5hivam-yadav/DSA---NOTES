/*
Problem: Find Min Max
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Search Tree
Statement: Given a BST root, return its minimum and maximum values by walking to
the leftmost and rightmost nodes. Sample Input: root = [5,3,8,2,4,7,9] Sample
Output: min = 2, max = 9 Explanation: Leftmost node is 2, rightmost is 9.
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
int findMin(TreeNode *r) {
    while (r && r->left)
        r = r->left;
    return r ? r->val : -1;
}
int findMax(TreeNode *r) {
    while (r && r->right)
        r = r->right;
    return r ? r->val : -1;
}

/*
Approach:
Leftmost/rightmost.
Time Complexity:
O(h)
Space Complexity:
O(1)
Key Idea:
Extreme descent.
*/
