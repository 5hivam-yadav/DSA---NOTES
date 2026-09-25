/*
Problem: Morris Inorder
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given a binary tree root, return inorder traversal in O(1) space with Morris threading (temporary predecessor links).
Sample Input: root = [1,2,3,4,5]
Sample Output: [4,2,5,1,3]
Explanation: Threaded walk yields sorted inorder.
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
vector<int> morris(TreeNode* r) {
    vector<int> o;
    while (r) {
        if (!r->left) {
            o.push_back(r->val);
            r = r->right;
        }
        else {
            auto p = r->left;
            while (p->right && p->right != r) p = p->right;
            if (!p->right) {
                p->right = r;
                r = r->left;
            }
            else {
                p->right = nullptr;
                o.push_back(r->val);
                r = r->right;
            }
        }
    }
    return o;
}

/*
Approach:
Thread + restore.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Predecessor link.
*/
