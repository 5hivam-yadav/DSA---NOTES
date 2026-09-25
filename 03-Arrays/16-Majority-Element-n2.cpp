/*
Problem: Majority Element n/2
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Hashing
Statement: Given an array of size n, return the element appearing more than n/2 times (guaranteed to exist; Boyer-Moore).
Sample Input: nums = [3, 2, 3]
Sample Output: 3
Explanation: 3 appears twice out of three elements.
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
    int majorityElement(vector<int>& a) {
        int c = 0, el = 0;
        for (int x : a) {
            if (c == 0) el = x;
            c += (x == el ? 1 : -1);
        }
        return el;
    }
};

int main() {
    vector<int> nums = {3, 2, 3};

    Solution sol;
    auto ans = sol.majorityElement(nums);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Cancel pairs.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Moore voting.
*/
