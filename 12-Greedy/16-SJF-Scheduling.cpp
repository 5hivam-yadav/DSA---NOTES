/*
Problem: Sjf Scheduling
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Greedy
Statement: Given burst times, schedule shortest-job-first (non-preemptive) to
minimize average waiting time. Sample Input: bt = [6,8,7,3] Sample Output: order
[3,6,7,8] Explanation: Shortest bursts run first.
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

double sjf(vector<int> &b) {
    sort(b.begin(), b.end());
    long long wait = 0, t = 0;
    for (int x : b) {
        wait += t;
        t += x;
    }
    return (double)wait / b.size();
}

int main() {
    vector<int> bt = {6, 8, 7, 3};

    auto ans = sjf(bt);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Shortest first.
Time Complexity:
O(n log n)
Space Complexity:
O(1)
Key Idea:
Minimizes avg wait.
*/
