/*
Problem: Largest Element
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Arrays
Statement: Given an integer array, return its largest element with a single
linear scan. Sample Input: a = [3, 7, 2, 9, 4] Sample Output: 9 Explanation: 9
is the maximum of the sample array.
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

int largest(vector<int> &a) {
    int m = a[0];
    for (int x : a)
        m = max(m, x);
    return m;
}

int main() {
    vector<int> a = {3, 7, 2, 9, 4};

    auto ans = largest(a);
    cout << ans << endl;
    return 0;
}

/*
Approach:
One max scan.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Track max.
*/
