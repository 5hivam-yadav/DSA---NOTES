/*
Problem: Merge Two BSTs
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search Tree
Statement: Given two BST roots, return all values in sorted order (two inorder traversals, then merge).
Sample Input: r1 = [2,1,4], r2 = [1,0,3]
Sample Output: [0,1,1,2,3,4]
Explanation: Merged inorder lists sort fully.
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
    void ino(TreeNode* r, vector<int>& o) {
        if (!r) return;
        ino(r->left, o);
        o.push_back(r->val);
        ino(r->right, o);
    }
    vector<int> getAllElements(TreeNode* a, TreeNode* b) {
        vector<int> x, y;
        ino(a, x);
        ino(b, y);
        vector<int> r;
        size_t i = 0, j = 0;
        while (i < x.size() && j < y.size()) r.push_back(x[i] < y[j] ? x[i++] : y[j++]);
        while (i < x.size()) r.push_back(x[i++]);
        while (j < y.size()) r.push_back(y[j++]);
        return r;
    }
};

/*
Approach:
Two inorders + merge.
Time Complexity:
O(n+m)
Space Complexity:
O(n+m)
Key Idea:
Sorted merge.
*/
