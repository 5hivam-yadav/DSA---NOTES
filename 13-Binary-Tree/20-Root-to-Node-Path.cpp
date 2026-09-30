/*
Problem: Root to Node Path
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Binary Tree
Statement: Given a binary tree root and target value, return the path from root
to that node (DFS with backtrack). Sample Input: root = [1,2,3,4,5], target = 5
Sample Output: [1,2,5]
Explanation: 1 -> 2 -> 5 reaches the target.
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
bool path(TreeNode *r, int x, vector<int> &p) {
    if (!r)
        return false;
    p.push_back(r->val);
    if (r->val == x)
        return true;
    if (path(r->left, x, p) || path(r->right, x, p))
        return true;
    p.pop_back();
    return false;
}

/*
Approach:
Push, recurse, pop.
Time Complexity:
O(n)
Space Complexity:
O(h)
Key Idea:
Backtrack path.
*/
