/*
Problem: Longest Consecutive Sequence
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Hashing
Statement: Given an unsorted array, return the length of the longest run of consecutive integers in O(n) with a hash set.
Sample Input: nums = [100, 4, 200, 1, 3, 2]
Sample Output: 4
Explanation: [1, 2, 3, 4] is the longest run.
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
    int longestConsecutive(vector<int>& a) {
        unordered_set<int> s(a.begin(), a.end());
        int b = 0;
        for (int x : s) {
            if (!s.count(x - 1)) {
                int c = x, l = 1;
                while (s.count(c + 1)) {
                    c++;
                    l++;
                }
                b = max(b, l);
            }
        }
        return b;
    }
};

int main() {
    vector<int> nums = {100, 4, 200, 1, 3, 2};

    Solution sol;
    auto ans = sol.longestConsecutive(nums);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Start-of-run only.
Time Complexity:
O(n) avg
Space Complexity:
O(n)
Key Idea:
Set streaks.
*/
