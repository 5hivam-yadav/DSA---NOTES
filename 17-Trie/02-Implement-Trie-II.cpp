/*
Problem: Implement Trie II
Platform: GFG / LeetCode
Problem Number: -
Difficulty: Medium
Pattern: Trie
Statement: Implement a trie that counts words and prefixes: insert, countWordsEqualTo, countWordsStartingWith, erase.
Sample Input: insert("apple") x2, countWordsEqualTo("apple")
Sample Output: 2
Explanation: Two copies of apple were inserted.
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

struct N {
    N* ch[26] = {};
    int pref = 0, end = 0;
};

struct Trie2 {
    N* r = new N();
    void ins(string s) {
        auto t = r;
        for (char c : s) {
            int i = c - 'a';
            if (!t->ch[i]) t->ch[i] = new N();
            t = t->ch[i];
            t->pref++;
        }
        t->end++;
    }
    int countWords(string s) {
        auto t = r;
        for (char c : s) {
            int i = c - 'a';
            if (!t->ch[i]) return 0;
            t = t->ch[i];
        }
        return t->end;
    }
    int countPref(string s) {
        auto t = r;
        for (char c : s) {
            int i = c - 'a';
            if (!t->ch[i]) return 0;
            t = t->ch[i];
        }
        return t->pref;
    }
    void erase(string s) {
        auto t = r;
        for (char c : s) {
            int i = c - 'a';
            t = t->ch[i];
            t->pref--;
        }
        t->end--;
    }
};

/*
Approach:
pref/end counters.
Time Complexity:
O(L)
Space Complexity:
O(nodes)
Key Idea:
Count pass-through.
*/
