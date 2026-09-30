/*
Problem: Implement Trie II
Platform: GFG / LeetCode
Problem Number: -
Difficulty: Medium
Pattern: Trie
Statement: Implement a trie that counts words and prefixes: insert,
countWordsEqualTo, countWordsStartingWith, erase. Sample Input: insert("apple")
x2, countWordsEqualTo("apple") Sample Output: 2 Explanation: Two copies of apple
were inserted.
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

struct N {
    N *ch[26] = {};
    int pref = 0, end = 0;
};

struct Trie2 {
    N *r = new N();
    void ins(string s) {
        auto t = r;
        for (char c : s) {
            int i = c - 'a';
            if (!t->ch[i])
                t->ch[i] = new N();
            t = t->ch[i];
            t->pref++;
        }
        t->end++;
    }
    int countWords(string s) {
        auto t = r;
        for (char c : s) {
            int i = c - 'a';
            if (!t->ch[i])
                return 0;
            t = t->ch[i];
        }
        return t->end;
    }
    int countPref(string s) {
        auto t = r;
        for (char c : s) {
            int i = c - 'a';
            if (!t->ch[i])
                return 0;
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
