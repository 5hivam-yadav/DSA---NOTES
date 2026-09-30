/*
Problem: Binary Search Tree Iterator
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Search Tree
Statement: Implement a BST iterator with next() and hasNext() in amortized O(1)
using a controlled inorder stack. Sample Input: root = [7,3,15,null,null,9,20],
ops next,next Sample Output: 3, 7 Explanation: Inorder yields 3 then 7.
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

class BSTIterator {
    stack<TreeNode *> st;
    void pushL(TreeNode *r) {
        while (r) {
            st.push(r);
            r = r->left;
        }
    }

  public:
    BSTIterator(TreeNode *r) { pushL(r); }
    int next() {
        auto n = st.top();
        st.pop();
        pushL(n->right);
        return n->val;
    }
    bool hasNext() { return !st.empty(); }
};

/*
Approach:
Left spine stack.
Time Complexity:
O(1) amortized
Space Complexity:
O(h)
Key Idea:
Controlled inorder.
*/
