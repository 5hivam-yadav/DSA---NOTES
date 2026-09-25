/*
Problem: Max Sum Non Adjacent
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: DP - 1D
Statement: Given an array, return the maximum sum picking no adjacent elements (take/skip DP).
Sample Input: a = [2, 1, 4, 9]
Sample Output: 11
Explanation: Pick 2 + 9 = 11.
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

int nonAdj(vector<int>& a) {
    int p2 = 0, p1 = 0;
    for (int x : a) {
        int c = max(p1, p2 + x);
        p2 = p1;
        p1 = c;
    }
    return p1;
}

int main() {
    vector<int> a = {2, 1, 4, 9};

    auto ans = nonAdj(a);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Take or skip.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
House robber core.
*/
