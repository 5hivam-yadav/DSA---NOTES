/*
Problem: Linear Search
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Arrays
Statement: Given an array and a value x, return the first index of x, or -1 if absent.
Sample Input: a = [4, 2, 7, 1], x = 7
Sample Output: 2
Explanation: 7 sits at index 2.
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

int linearSearch(vector<int>& a, int x) {
    for (int i = 0; i < (int)a.size(); i++) if (a[i] == x) return i;
    return -1;
}

int main() {
    vector<int> a = {4, 2, 7, 1};
    int x = 7;

    auto ans = linearSearch(a, x);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Scan each element.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Unsorted fallback.
*/
