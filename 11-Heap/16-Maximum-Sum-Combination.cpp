/*
Problem: Maximum Sum Combination
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Backtracking
Statement: Given arrays A, B and k, return the k maximum sums of pairs (a in A, b in B) using a max-heap + visited set.
Sample Input: A = [4,2,5,1], B = [8,0,3,5], k = 3
Sample Output: [13, 12, 10]
Explanation: Pairs (5,8),(4,8),(5,5) give top sums.
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

vector<int> maxComb(vector<int>& a, vector<int>& b, int k) {
    sort(a.begin(), a.end(), greater<int>());
    sort(b.begin(), b.end(), greater<int>());
    int n = a.size();
    priority_queue<tuple<int, int, int>> pq;
    set<pair<int, int>> vis;
    pq.push({a[0] + b[0], 0, 0});
    vis.insert({0, 0});
    vector<int> r;
    while (k-- && !pq.empty()) {
        auto [s, i, j] = pq.top();
        pq.pop();
        r.push_back(s);
        if (i + 1 < n && !vis.count({i + 1, j})) {
            vis.insert({i + 1, j});
            pq.push({a[i + 1] + b[j], i + 1, j});
        }
        if (j + 1 < n && !vis.count({i, j + 1})) {
            vis.insert({i, j + 1});
            pq.push({a[i] + b[j + 1], i, j + 1});
        }
    }
    return r;
}

int main() {
    vector<int> A = {4, 2, 5, 1};
    vector<int> B = {8, 0, 3, 5};
    int k = 3;

    auto ans = maxComb(A, B, k);
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Best-first neighbors.
Time Complexity:
O((n + k) log k)
Space Complexity:
O(k)
Key Idea:
Visited index pairs.
*/
