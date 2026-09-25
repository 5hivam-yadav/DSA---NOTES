/*
Problem: Word Ladder I
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Graph (BFS/DFS)
Statement: Given beginWord, endWord and a word list, return the shortest transformation length changing one letter at a time (BFS).
Sample Input: begin = "hit", end = "cog", list has hot,dot,lot,log,cog
Sample Output: 5
Explanation: hit->hot->dot->lot->log->cog is 5 words.
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

class Solution {
public:
    int ladderLength(string b, string e, vector<string>& w) {
        unordered_set<string> s(w.begin(), w.end());
        if (!s.count(e)) return 0;
        queue<string> q;
        q.push(b);
        int d = 1;
        unordered_set<string> v;
        v.insert(b);
        while (!q.empty()) {
            int n = q.size();
            while (n--) {
                string c = q.front();
                q.pop();
                if (c == e) return d;
                for (size_t i = 0; i < c.size(); i++) {
                    string t = c;
                    for (char ch = 'a'; ch <= 'z'; ch++) {
                        t[i] = ch;
                        if (s.count(t) && !v.count(t)) {
                            v.insert(t);
                            q.push(t);
                        }
                    }
                }
            }
            d++;
        }
        return 0;
    }
};
  // Bidirectional BFS faster.

/*
Approach:
BFS word graph.
Time Complexity:
O(N L 26)
Space Complexity:
O(N L)
Key Idea:
One-letter edges.
*/
