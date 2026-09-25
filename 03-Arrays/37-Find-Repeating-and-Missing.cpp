/*
Problem: Find Repeating and Missing
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Arrays
Statement: Given an array of 1..n with one value duplicated and one missing, return [repeating, missing].
Sample Input: a = [3, 1, 2, 5, 3]
Sample Output: [3, 4]
Explanation: 3 appears twice and 4 never appears.
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

pair<int, int> repMiss(vector<int>& a) {
    int n = a.size();
    long long s = 0, q = 0;
    for (int x : a) {
        s += x;
        q += 1LL * x * x;
    }
    long long es = 1LL * n * (n + 1) / 2, eq = 1LL * n * (n + 1) * (2 * n + 1) / 6;
    long long d = s - es, d2 = q - eq;
    long long sum = d2 / d;
    int rep = (int)((d + sum) / 2), miss = (int)(sum - rep);
    return { rep, miss};
}

int main() {
    vector<int> a = {3, 1, 2, 5, 3};

    auto ans = repMiss(a);
    cout << ans.first << " " << ans.second << endl;
    return 0;
}

/*
Approach:
Sum + sum-squares equations.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Two equations two unknowns.
*/
