/*
Problem: Subset Sum I
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Backtracking
Statement: Given an array, return all possible subset sums in sorted order (take/skip recursion).
Sample Input: a = [2,3]
Sample Output: [0,2,3,5]
Explanation: Sums of [], [2], [3], [2,3].
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

void f(int i, vector<int>& a, int s, vector<int>& r) {
    if (i == (int)a.size()) {
        r.push_back(s);
        return;
    }
    f(i + 1, a, s + a[i], r);
    f(i + 1, a, s, r);
}

int main() {
    vector<int> a = {2, 3};
    vector<int> r;
    f(0, a, 0, r);
    sort(r.begin(), r.end());
    for (size_t i = 0; i < r.size(); i++) cout << r[i] << (i + 1 < r.size() ? " " : "");
    cout << endl;
    return 0;
}

/*
Approach:
Add or skip.
Time Complexity:
O(2^n)
Space Complexity:
O(n)
Key Idea:
Sum state.
*/
