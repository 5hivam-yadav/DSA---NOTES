/*
Problem: Floyd Warshall
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Hard
Pattern: Shortest Path
Statement: Given an adjacency matrix, replace each entry with the all-pairs shortest distance (try every intermediate k).
Sample Input: dist = [[0,3,INF],[INF,0,1],[2,INF,0]]
Sample Output: [[0,3,4],[3,0,1],[2,5,0]]
Explanation: Path 0->1->2 costs 4, beating INF.
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

void floyd(vector<vector<long long>>& d) {
    int n = d.size();
    for (int k = 0; k < n; k++) for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (d[i][k] + d[k][j] < d[i][j]) d[i][j] = d[i][k] + d[k][j];
}

/*
Approach:
Via-k triple loop.
Time Complexity:
O(V^3)
Space Complexity:
O(V^2)
Key Idea:
All-pairs DP.
*/
