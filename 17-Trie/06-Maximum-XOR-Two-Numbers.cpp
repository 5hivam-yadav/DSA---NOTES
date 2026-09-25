/*
Problem: Maximum XOR Two Numbers
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Trie
Statement: Given an array, return the maximum XOR of any two numbers using a binary trie.
Sample Input: nums = [3, 10, 5, 25, 2, 8]
Sample Output: 28
Explanation: 5 xor 25 = 28, the maximum pair.
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

struct BT2 {
    struct Nd {
        Nd* ch[2] = {};
    };
    Nd* r = new Nd();
    void ins(int x) {
        auto t = r;
        for (int b = 31; b >= 0; b--) {
            int bit = (x >> b) & 1;
            if (!t->ch[bit]) t->ch[bit] = new Nd();
            t = t->ch[bit];
        }
    }
    int q(int x) {
        auto t = r;
        int ans = 0;
        for (int b = 31; b >= 0; b--) {
            int bit = (x >> b) & 1;
            if (t->ch[bit ^ 1]) {
                ans |= 1 << b;
                t = t->ch[bit ^ 1];
            }
            else t = t->ch[bit];
        }
        return ans;
    }
};

class Solution {
public:
    int findMaximumXOR(vector<int>& a) {
        BT2 t;
        for (int x : a) t.ins(x);
        int b = 0;
        for (int x : a) b = max(b, t.q(x));
        return b;
    }
};

int main() {
    vector<int> nums = {3, 10, 5, 25, 2, 8};

    Solution sol;
    auto ans = sol.findMaximumXOR(nums);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Opposite-bit greedy.
Time Complexity:
O(32n)
Space Complexity:
O(32n)
Key Idea:
XOR max path.
*/
