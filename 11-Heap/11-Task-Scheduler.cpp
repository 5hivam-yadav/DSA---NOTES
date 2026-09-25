/*
Problem: Task Scheduler
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Heap / Priority Queue
Statement: Given tasks and cooldown n, find the minimum intervals to finish all (formula from max frequency).
Sample Input: tasks = [A,A,A,B,B,B], n = 2
Sample Output: 8
Explanation: Pattern A B idle A B idle A B needs 8 slots.
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
    int leastInterval(vector<char>& t, int n) {
        int f[26] = {0}, mx = 0, cnt = 0;
        for (char c : t) {
            f[c - 'A']++;
            mx = max(mx, f[c - 'A']);
        }
        for (int x : f) if (x == mx) cnt++;
        return max((int)t.size(), (mx - 1) * (n + 1) + cnt);
    }
};

/*
Approach:
Idle slots math.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Max freq frame.
*/
