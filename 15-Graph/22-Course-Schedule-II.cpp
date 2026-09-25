/*
Problem: Course Schedule II
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Topological Sort
Statement: Given numCourses and prerequisites, return an order finishing all courses, or [] if a cycle exists.
Sample Input: n = 2, prereq = [[1,0]]
Sample Output: [0,1]
Explanation: Take 0 before 1.
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
    vector<int> findOrder(int n, vector<vector<int>>& p) {
        vector<vector<int>> g(n);
        vector<int> in(n, 0);
        for (auto& e : p) {
            g[e[1]].push_back(e[0]);
            in[e[0]]++;
        }
        queue<int> q;
        for (int i = 0; i < n; i++) if (!in[i]) q.push(i);
        vector<int> o;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            o.push_back(u);
            for (int v : g[u]) if (--in[v] == 0) q.push(v);
        }
        return (int)o.size() == n ? o : vector<int>();
    }
};

int main() {
    int n = 2;
    vector<vector<int>> prereq = {{1, 0}};

    Solution sol;
    auto ans = sol.findOrder(n, prereq);
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Return order or empty.
Time Complexity:
O(V+E)
Space Complexity:
O(V+E)
Key Idea:
Kahn order.
*/
