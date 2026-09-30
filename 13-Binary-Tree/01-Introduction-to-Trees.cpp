/*
Problem: Introduction to Trees
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Tree
Statement: Introduce binary tree basics: build a root with left/right children
and traverse it (preorder demo). Sample Input: values = [1,2,3] Sample Output:
preorder [1,2,3] Explanation: Root 1 visited before children 2 and 3.
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
// Tree: nodes + edges, root, parent/child, leaf, height/depth.

/*
Approach:
Learn terms.
Time Complexity:
O(1)
Space Complexity:
O(1)
Key Idea:
Vocabulary first.
*/
