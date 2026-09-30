/*
Problem: Reverse an Array
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Basics
Statement: Given an array, reverse it in place with two pointers swapping ends
toward the centre. Sample Input: a = [1, 2, 3, 4] Sample Output: [4, 3, 2, 1]
Explanation: Ends swap inward until they meet.
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

void rev(vector<int> &a, int l, int r) {
    if (l >= r)
        return;
    swap(a[l], a[r]);
    rev(a, l + 1, r - 1);
}
// Iterative two pointers also O(n)/O(1).

/*
Approach:
1. Swap ends.
2. Recurse inward.
Time Complexity:
O(n)
Space Complexity:
O(n) stack
Key Idea:
Two pointers can be recursive.
*/
