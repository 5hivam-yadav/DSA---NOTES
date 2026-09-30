/*
Problem: Offline XOR Queries
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Bit Manipulation
Statement: Given an array and queries (x, m), return max xor of x with elements
up to index m using an offline binary trie. Sample Input: a = [0,1,2,3,4], query
x=3,m=1 Sample Output: 3 Explanation: Best partner within [0,1] is 0 (3 xor 0 =
3).
*/
#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

// Full driver: sort queries [xi, mi, idx]; insert nums <= mi; answer
// maxXor(xi). See file 05.

/*
Approach:
Same as 05.
Time Complexity:
O((n+q) log C)
Space Complexity:
O(n log C)
Key Idea:
Same as 05.
*/
