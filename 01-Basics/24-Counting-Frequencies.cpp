/*
Problem: Counting Frequencies
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Basics
Statement: Given an array with values in 1..k, return the frequency of each
value. Sample Input: a = [1, 2, 1, 3, 2, 1], k = 3 Sample Output: [3, 2, 1]
Explanation: 1 appears 3 times, 2 twice, 3 once.
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

vector<int> freq(vector<int> &a, int k) {
    vector<int> f(k, 0);
    for (int x : a)
        if (x >= 1 && x <= k)
            f[x - 1]++;
    return f;
}

int main() {
    vector<int> a = {1, 2, 1, 3, 2, 1};
    int k = 3;

    auto ans = freq(a, k);
    for (int i = 0; i < (int)ans.size(); i++)
        cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
1. Size-k array.
2. Count once.
Time Complexity:
O(n)
Space Complexity:
O(k)
Key Idea:
Count once, answer queries O(1).
*/
