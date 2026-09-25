/*
Problem: Fractional Knapsack
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Greedy
Statement: Given weights, values and capacity, take fractions to maximize value by value/weight ratio.
Sample Input: wt = [10,20,30], val = [60,100,120], W = 50
Sample Output: 240.0
Explanation: Take all of 10 and 20 plus 2/3 of 30.
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

double fracKnap(vector<int>& v, vector<int>& w, int W) {
    int n = v.size();
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b) { return 1.0 * v[a] / w[a] > 1.0 * v[b] / w[b]; });
    double ans = 0;
    for (int i : idx) {
        if (W >= w[i]) {
            ans += v[i];
            W -= w[i];
        }
        else {
            ans += 1.0 * v[i] / w[i] * W;
            break;
        }
    }
    return ans;
}

int main() {
    vector<int> wt = {10, 20, 30};
    vector<int> val = {60, 100, 120};
    int W = 50;

    auto ans = fracKnap(val, wt, W);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Ratio order.
Time Complexity:
O(n log n)
Space Complexity:
O(n)
Key Idea:
Greedy works (fractional).
*/
