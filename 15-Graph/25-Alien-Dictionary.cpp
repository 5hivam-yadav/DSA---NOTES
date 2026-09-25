/*
Problem: Alien Dictionary
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Topological Sort
Statement: Given sorted words in an alien language, return a valid alphabet order via topological sort of precedence edges.
Sample Input: words = ["wrt","wrf","er","ett","rftt"]
Sample Output: "wertf"
Explanation: Edges w->e, r->t, t->f, e->r order as wertf.
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

string alien(vector<string>& w, int K) {
    vector<vector<int>> g(K);
    vector<int> in(K, 0);
    vector<vector<char>> seen(K, vector<char>(K, 0));
    for (size_t i = 0; i + 1 < w.size(); i++) {
        string& a = w[i];
        string& b = w[i+1];
        size_t n = min(a.size(), b.size());
        for (size_t j = 0; j < n; j++) {
            if (a[j] != b[j]) {
                int u = a[j] - 'a', v = b[j] - 'a';
                if (!seen[u][v]) {
                    g[u].push_back(v);
                    in[v]++;
                    seen[u][v] = 1;
                }
                break;
            }
        }
    }
    queue<int> q;
    for (int i = 0; i < K; i++) if (!in[i]) q.push(i);
    string o;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        o += char('a' + u);
        for (int v : g[u]) if (--in[v] == 0) q.push(v);
    }
    return (int)o.size() == K ? o : "";
}

/*
Approach:
First-diff edges + Kahn.
Time Complexity:
O(N*L + K)
Space Complexity:
O(K^2)
Key Idea:
Prefix invalid => empty.
*/
