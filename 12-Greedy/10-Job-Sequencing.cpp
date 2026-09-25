/*
Problem: Job Sequencing
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Greedy
Statement: Given jobs with deadlines and profits, schedule at most one per slot for maximum profit (sort by profit, DSU/slots).
Sample Input: jobs = [(1,4,20),(2,1,10),(3,1,40),(4,1,30)]
Sample Output: (2 jobs, profit 60)
Explanation: Jobs 1 and 3 fit for 20 + 40 = 60.
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

pair<int, int> jobs(vector<int>& id, vector<int>& dl, vector<int>& pf) {
    int n = id.size(), mx = *max_element(dl.begin(), dl.end());
    vector<int> slot(mx + 1, -1);
    vector<int> o(n);
    iota(o.begin(), o.end(), 0);
    sort(o.begin(), o.end(), [&](int a, int b) { return pf[a] > pf[b]; });
    int c = 0, p = 0;
    for (int i : o) {
        for (int d = dl[i]; d > 0; d--) if (slot[d] == -1) {
            slot[d] = i;
            c++;
            p += pf[i];
            break;
        }
    }
    return { c, p};
}

/*
Approach:
Profit order + latest slot.
Time Complexity:
O(n * maxD)
Space Complexity:
O(maxD)
Key Idea:
DSU speeds slots.
*/
