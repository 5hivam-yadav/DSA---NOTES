/*
Problem: Ceil and Floor
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search Tree
Statement: Given a BST root and key, return the ceil (smallest >= key) and floor (largest <= key).
Sample Input: root = [8,4,12,2,6,10,14], key = 5
Sample Output: ceil 6, floor 4
Explanation: 6 is next above 5; 4 next below.
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
int ceilBST(TreeNode* r, int x) {
    int c = -1;
    while (r) {
        if (r->val >= x) {
            c = r->val;
            r = r->left;
        }
        else r = r->right;
    }
    return c;
}
int floorBST(TreeNode* r, int x) {
    int f = -1;
    while (r) {
        if (r->val <= x) {
            f = r->val;
            r = r->right;
        }
        else r = r->left;
    }
    return f;
}

/*
Approach:
Track candidate.
Time Complexity:
O(h)
Space Complexity:
O(1)
Key Idea:
Bound walk.
*/
