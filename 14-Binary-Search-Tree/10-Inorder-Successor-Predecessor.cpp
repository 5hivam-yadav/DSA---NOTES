/*
Problem: Inorder Successor Predecessor
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search Tree
Statement: Given a BST root and key x, return the inorder successor (smallest >
x) and predecessor (largest < x). Sample Input: root = [20,8,22,4,12,10,14], x =
8 Sample Output: predecessor = 4, successor = 10 Explanation: 4 is the largest
key below 8; 10 the smallest above.
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
int succ(TreeNode *r, int x) {
    int s = -1;
    while (r) {
        if (r->val > x) {
            s = r->val;
            r = r->left;
        } else
            r = r->right;
    }
    return s;
}
int pred(TreeNode *r, int x) {
    int p = -1;
    while (r) {
        if (r->val < x) {
            p = r->val;
            r = r->right;
        } else
            r = r->left;
    }
    return p;
}

/*
Approach:
Track candidate.
Time Complexity:
O(h)
Space Complexity:
O(1)
Key Idea:
Tighten bound.
*/
