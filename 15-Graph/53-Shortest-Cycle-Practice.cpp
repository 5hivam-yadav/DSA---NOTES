/*
Problem: Shortest Cycle Practice
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Shortest Path
Statement: Given an undirected graph, return the length of its shortest cycle, or -1 if acyclic (BFS from every node).
Sample Input: n = 4, edges = [[0,1],[1,2],[2,3],[3,0]]
Sample Output: 4
Explanation: The square is a 4-cycle.
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

  // BFS from each node for shortest cycle in UG; see files 18-24 for cycle/topo.

/*
Approach:
BFS per node.
Time Complexity:
O(V(V+E))
Space Complexity:
O(V)
Key Idea:
Extension drill.
*/
