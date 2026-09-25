/*
Problem: Sort Colors 0-1-2
Platform: GFG / Striver A2Z
Problem Number: -
Difficulty: Medium
Pattern: Two Pointers
Statement: Given an array of 0s, 1s and 2s, sort it in place (Dutch national flag).
Sample Input: nums = [2, 0, 2, 1, 1, 0]
Sample Output: [0, 0, 1, 1, 2, 2]
Explanation: Grouped by value in one pass, O(1) space.
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
    void sortColors(vector<int>& a) {
        int l = 0, m = 0, r = (int)a.size() - 1;
        while (m <= r) {
            if (a[m] == 0) swap(a[l++], a[m++]);
            else if (a[m] == 1) m++;
            else swap(a[m], a[r--]);
        }
    }
};

int main() {
    vector<int> nums = {2, 0, 2, 1, 1, 0};

    Solution sol;
    sol.sortColors(nums);
    for (int i = 0; i < (int)nums.size(); i++) cout << nums[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
0 front, 2 back.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Dutch flag.
*/
