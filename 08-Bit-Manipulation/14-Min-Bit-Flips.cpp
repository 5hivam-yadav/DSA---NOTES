/*
Problem: Min Bit Flips
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Bit Manipulation
Statement: Given start and goal, return the minimum bit flips to convert one to the other (popcount of start^goal).
Sample Input: start = 10, goal = 7
Sample Output: 3
Explanation: 10^7 = 13 (1101) which has three 1s.
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
    int minBitFlips(int a, int b) {
        int x = a ^ b, c = 0;
        while (x) {
            x &= x - 1;
            c++;
        }
        return c;
    }
};

int main() {
    int start = 10;
    int goal = 7;

    Solution sol;
    auto ans = sol.minBitFlips(start, goal);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Popcount of XOR.
Time Complexity:
O(1)
Space Complexity:
O(1)
Key Idea:
Differing bits.
*/
