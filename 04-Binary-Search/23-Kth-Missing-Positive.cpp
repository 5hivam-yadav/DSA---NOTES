/*
Problem: Kth Missing Positive
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Binary Search on Answer
Statement: Given a strictly increasing array, return the k-th missing positive integer in O(log n).
Sample Input: arr = [2,3,4,7,11], k = 5
Sample Output: 9
Explanation: Missing are 1,5,6,8,9; the 5th is 9.
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

class Solution {
public:
    int findKthPositive(vector<int>& a, int k) {
        int lo = 0, hi = (int)a.size();
        while (lo < hi) {
            int m = lo + (hi - lo) / 2;
            if (a[m] - (m + 1) < k) lo = m + 1;
            else hi = m;
        }
        return lo + k;
    }
};

int main() {
    vector<int> arr = {2, 3, 4, 7, 11};
    int k = 5;

    Solution sol;
    auto ans = sol.findKthPositive(arr, k);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Missing = a[i]-(i+1).
Time Complexity:
O(log n)
Space Complexity:
O(1)
Key Idea:
Missing count predicate.
*/
