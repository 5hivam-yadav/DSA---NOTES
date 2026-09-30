/*
Problem: Max Consecutive Ones
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Sliding Window
Statement: Given a binary array, return the maximum number of consecutive 1s.
Sample Input: a = [1, 1, 0, 1, 1, 1]
Sample Output: 3
Explanation: The longest run of 1s has length 3.
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

class Solution {
  public:
    int findMaxConsecutiveOnes(vector<int> &a) {
        int b = 0, c = 0;
        for (int x : a) {
            c = (x == 1 ? c + 1 : 0);
            b = max(b, c);
        }
        return b;
    }
};

int main() {
    vector<int> a = {1, 1, 0, 1, 1, 1};

    Solution sol;
    auto ans = sol.findMaxConsecutiveOnes(a);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Run count.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Run length.
*/
