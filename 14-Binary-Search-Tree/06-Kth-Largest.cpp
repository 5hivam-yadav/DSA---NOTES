/*
Problem: Kth Largest
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search Tree
Statement: Given a BST root and k, return the k-th largest value via reverse inorder.
Sample Input: root = [3,1,4,null,2], k = 2
Sample Output: 3
Explanation: Descending order is 4,3,2,1; 2nd is 3.
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
int k2, c2 = 0, a2 = -1;
void fr(TreeNode* r) {
    if (!r || a2 != -1) return;
    fr(r->right);
    if (++c2 == k2) a2 = r->val;
    fr(r->left);
}
int kthLargest(TreeNode* r, int k) {
    k2 = k;
    c2 = 0;
    a2 = -1;
    fr(r);
    return a2;
}

/*
Approach:
Reverse inorder.
Time Complexity:
O(n)
Space Complexity:
O(h)
Key Idea:
Right-first.
*/
