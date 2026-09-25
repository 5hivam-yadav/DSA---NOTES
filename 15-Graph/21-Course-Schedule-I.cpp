/*
Problem: Course Schedule I
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Topological Sort
Statement: Given numCourses and prerequisites, return true if all courses finish (no directed cycle; Kahn or DFS).
Sample Input: n = 2, prereq = [[1,0]]
Sample Output: true
Explanation: Take 0 then 1; no cycle.
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
    bool canFinish(int n, vector<vector<int>>& p) {
        vector<vector<int>> g(n);
        vector<int> in(n, 0);
        for (auto& e : p) {
            g[e[1]].push_back(e[0]);
            in[e[0]]++;
        }
        queue<int> q;
        for (int i = 0; i < n; i++) if (!in[i]) q.push(i);
        int c = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            c++;
            for (int v : g[u]) if (--in[v] == 0) q.push(v);
        }
        return c == n;
    }
};

int main() {
    int n = 2;
    vector<vector<int>> prereq = {{1, 0}};

    Solution sol;
    auto ans = sol.canFinish(n, prereq);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
Kahn count.
Time Complexity:
O(V+E)
Space Complexity:
O(V+E)
Key Idea:
Cycle => c<n.
*/
