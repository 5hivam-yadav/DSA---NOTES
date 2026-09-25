/*
Problem: Serialize Deserialize
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Binary Tree
Statement: Serialize a binary tree to a string (level order with nulls) and deserialize it back exactly.
Sample Input: root = [1,2,3,null,null,4,5]
Sample Output: "1,2,3,null,null,4,5"
Explanation: Round trip preserves shape and values.
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

class Codec {
public:
    string serialize(TreeNode* r) {
        if (!r) return "#,";
        return to_string(r->val) + "," + serialize(r->left) + serialize(r->right);
    }
    TreeNode* f(queue<string>& q) {
        string s = q.front();
        q.pop();
        if (s == "#") return nullptr;
        auto n = new TreeNode(stoi(s));
        n->left = f(q);
        n->right = f(q);
        return n;
    }
    TreeNode* deserialize(string s) {
        queue<string> q;
        string t;
        for (char c : s) {
            if (c == ',') {
                q.push(t);
                t = "";
            }
            else t += c;
        }
        return f(q);
    }
};

/*
Approach:
Preorder with #.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Marker rebuild.
*/
