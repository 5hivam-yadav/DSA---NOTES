/*
Problem: Word Ladder II
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Graph (BFS/DFS)
Statement: Given beginWord, endWord and a word list, return all shortest transformation sequences (BFS + backtrack).
Sample Input: begin = "hit", end = "cog"
Sample Output: [["hit","hot","lot","log","cog"]]
Explanation: One shortest chain of 5 words.
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
    vector<vector<string>> findLadders(string b, string e, vector<string>& w) {
        unordered_set<string> s(w.begin(), w.end());
        vector<vector<string>> ans;
        queue<vector<string>> q;
        q.push({b});
        unordered_set<string> vis;
        bool done = false;
        while (!q.empty() && !done) {
            int n = q.size();
            unordered_set<string> lvl;
            while (n--) {
                auto p = q.front();
                q.pop();
                string last = p.back();
                if (last == e) {
                    ans.push_back(p);
                    done = true;
                    continue;
                }
                for (size_t i = 0; i < last.size(); i++) {
                    string t = last;
                    for (char ch = 'a'; ch <= 'z'; ch++) {
                        t[i] = ch;
                        if (s.count(t) && !vis.count(t)) {
                            lvl.insert(t);
                            auto np = p;
                            np.push_back(t);
                            q.push(np);
                        }
                    }
                }
            }
            for (auto& x : lvl) vis.insert(x);
        }
        return ans;
    }
};

/*
Approach:
Level BFS + paths.
Time Complexity:
O(N L 26)
Space Complexity:
O(N L)
Key Idea:
Freeze visited per level.
*/
