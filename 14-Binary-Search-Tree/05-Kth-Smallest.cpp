/*
Problem: Kth Smallest
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search Tree
Statement: Given a BST root and k, return the k-th smallest value via inorder traversal.
Sample Input: root = [3,1,4,null,2], k = 2
Sample Output: 2
Explanation: Inorder is [1,2,3,4]; 2nd is 2.
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
    int k, cnt = 0, ans = -1;
    void f(TreeNode* r) {
        if (!r || ans != -1) return;
        f(r->left);
        if (++cnt == k) {
            ans = r->val;
            return;
        }
        f(r->right);
    }
    int kthSmallest(TreeNode* r, int kk) {
        k = kk;
        f(r);
        return ans;
    }
};

/*
Approach:
Inorder sorted.
Time Complexity:
O(n)
Space Complexity:
O(h)
Key Idea:
Counter stop.
*/
