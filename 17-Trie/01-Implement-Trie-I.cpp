/*
Problem: Implement Trie I
Platform: GFG / LeetCode
Problem Number: -
Difficulty: Medium
Pattern: Trie
Statement: Implement a trie with insert, search and startsWith for lowercase words, each in O(L) time.
Sample Input: insert("apple"), search("apple"), search("app"), startsWith("app")
Sample Output: true, false, true
Explanation: "apple" exists; "app" is only a prefix of it.
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

struct Node {
    Node* ch[26] = {};
    bool end = false;
};

class Trie {
    Node* r = new Node();
public:
    void insert(string s) {
        auto t = r;
        for (char c : s) {
            int i = c - 'a';
            if (!t->ch[i]) t->ch[i] = new Node();
            t = t->ch[i];
        }
        t->end = true;
    }
    bool search(string s) {
        auto t = r;
        for (char c : s) {
            int i = c - 'a';
            if (!t->ch[i]) return false;
            t = t->ch[i];
        }
        return t->end;
    }
    bool startsWith(string s) {
        auto t = r;
        for (char c : s) {
            int i = c - 'a';
            if (!t->ch[i]) return false;
            t = t->ch[i];
        }
        return true;
    }
};

/*
Approach:
Walk-or-create.
Time Complexity:
O(L)
Space Complexity:
O(nodes)
Key Idea:
Prefix tree.
*/
