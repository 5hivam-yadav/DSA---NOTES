/*
Problem: Merge Sorted Arrays
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Arrays
Statement: Given sorted arrays nums1 (with m elements plus n trailing zeros) and nums2, merge nums2 into nums1 in place from the back.
Sample Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
Sample Output: [1,2,2,3,5,6]
Explanation: Merged in place from the largest end.
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
    void merge(vector<int>& a, int m, vector<int>& b, int n) {
        int i = m - 1, j = n - 1, k = m + n - 1;
        while (i >= 0 && j >= 0) a[k--] = (a[i] > b[j] ? a[i--] : b[j--]);
        while (j >= 0) a[k--] = b[j--];
    }
};

int main() {
    vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    int m = 3;
    vector<int> nums2 = {2, 5, 6};
    int n = 3;

    Solution sol;
    sol.merge(nums1, m, nums2, n);
    for (int i = 0; i < (int)nums1.size(); i++) cout << nums1[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Fill from back.
Time Complexity:
O(m+n)
Space Complexity:
O(1)
Key Idea:
Back fill avoids shift.
*/
