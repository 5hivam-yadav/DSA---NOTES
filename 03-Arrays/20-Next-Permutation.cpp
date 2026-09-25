/*
Problem: Next Permutation
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Backtracking
Statement: Rearrange the array into the next lexicographically greater permutation in place; if none, sort ascending.
Sample Input: nums = [1, 2, 3]
Sample Output: [1, 3, 2]
Explanation: The next permutation swaps the tail to 1, 3, 2.
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
    void nextPermutation(vector<int>& a) {
        int n = a.size(), i = n - 2;
        while (i >= 0 && a[i] >= a[i + 1]) i--;
        if (i >= 0) {
            int j = n - 1;
            while (a[j] <= a[i]) j--;
            swap(a[i], a[j]);
        }
        reverse(a.begin() + i + 1, a.end());
    }
};

int main() {
    vector<int> nums = {1, 2, 3};

    Solution sol;
    sol.nextPermutation(nums);
    for (int i = 0; i < (int)nums.size(); i++) cout << nums[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Pivot swap reverse.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Lexicographic next.
*/
