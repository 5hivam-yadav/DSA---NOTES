/*
Problem: Morris Preorder
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given a binary tree root, return preorder traversal in O(1) space with Morris threading.
Sample Input: root = [1,2,3,4,5]
Sample Output: [1,2,4,5,3]
Explanation: Visit node before threading left.
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
vector<int> morrisPre(TreeNode* r) {
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
                o.push_back(r->val);
                r = r->left;
            }
            else {
                p->right = nullptr;
                r = r->right;
            }
        }
    }
    return o;
}

/*
Approach:
Visit before thread.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Preorder thread.
*/
