/*
Problem: Longest Word with All Prefixes
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Trie
Statement: Given words, return the longest word whose every prefix is also in
the list (trie walk; lexicographically smallest on ties). Sample Input: words =
["w","wo","wor","worl","world","banana"] Sample Output: "world" Explanation:
"world" builds one letter at a time.
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

struct A {
    bool end = false;
    int ch[26];
    A() {
        end = false;
        memset(ch, -1, sizeof ch);
    }
};
// Insert all; DFS only through end=true nodes; track longest (lex smallest
// tie). O(total length).

/*
Approach:
Only valid chain.
Time Complexity:
O(total L)
Space Complexity:
O(nodes)
Key Idea:
Prefix-valid path.
*/
