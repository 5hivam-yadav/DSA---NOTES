/*
Problem: Bit Prefix Max XOR
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Trie
Statement: Given an array and queries (x, m), answer max xor of x with elements up to index m using an offline binary trie.
Sample Input: a = [0,1,2,3,4], query x = 3, m = 1
Sample Output: 3
Explanation: Within [0,1], partner 0 gives 3 xor 0 = 3.
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

struct BT {
    struct Nd {
        Nd* ch[2] = {};
    };
    Nd* r = new Nd();
    void ins(int x) {
        auto t = r;
        for (int b = 17; b >= 0; b--) {
            int bit = (x >> b) & 1;
            if (!t->ch[bit]) t->ch[bit] = new Nd();
            t = t->ch[bit];
        }
    }
    int q(int x, int lim) {
        auto t = r;
        int ans = 0;
        for (int b = 17; b >= 0; b--) {
            int bit = (x >> b) & 1;
            if (t->ch[bit ^ 1]) {
                ans |= 1 << b;
                t = t->ch[bit ^ 1];
            }
            else if (t->ch[bit]) t = t->ch[bit];
            else return -1;
        }
        return ans;
    }
};
  // Sort nums + queries by limit; insert incrementally. O((n+q) log C).

/*
Approach:
Offline + binary trie.
Time Complexity:
O((n+q) log C)
Space Complexity:
O(n log C)
Key Idea:
Limit-sorted insert.
*/
