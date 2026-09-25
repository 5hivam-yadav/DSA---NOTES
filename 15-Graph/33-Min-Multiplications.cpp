/*
Problem: Min Multiplications
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Shortest Path
Statement: Given start, end and multipliers mod 100000, return the minimum multiplications (BFS over remainders).
Sample Input: start = 3, end = 30, arr = [2,5,7]
Sample Output: 2
Explanation: 3*2=6, 6*5=30 in two steps.
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

int minMult(vector<int>& a, int s, int e) {
    const int M = 100000;
    vector<int> d(M, INT_MAX);
    queue<int> q;
    q.push(s);
    d[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == e) return d[u];
        for (int x : a) {
            int v = (u * x) % M;
            if (d[v] == INT_MAX) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    return -1;
}

int main() {
    int start = 3;
    int end = 30;
    vector<int> arr = {2, 5, 7};

    auto ans = minMult(arr, start, end);
    cout << ans << endl;
    return 0;
}

/*
Approach:
BFS on mod graph.
Time Complexity:
O(M n)
Space Complexity:
O(M)
Key Idea:
State = value mod M.
*/
