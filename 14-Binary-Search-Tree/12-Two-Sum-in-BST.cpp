/*
Problem: Two Sum in Binary Search Tree
Platform: LeetCode
Problem Number: -
Difficulty: Easy
Pattern: Binary Search Tree
Statement: Given a BST root and k, return true if two nodes sum to k (inorder +
two pointers, or hash set). Sample Input: root = [5,3,6,2,4,null,7], k = 9
Sample Output: true
Explanation: 2 + 7 = 9.
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

class Solution {
  public:
    bool f(TreeNode *r, int k, unordered_set<int> &s) {
        if (!r)
            return false;
        if (s.count(k - r->val))
            return true;
        s.insert(r->val);
        return f(r->left, k, s) || f(r->right, k, s);
    }
    bool findTarget(TreeNode *r, int k) {
        unordered_set<int> s;
        return f(r, k, s);
    }
};
// Two iterators O(n)/O(h) also.

/*
Approach:
Complement set.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
DFS + hash.
*/
