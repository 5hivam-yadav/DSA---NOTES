/*
Problem: Find Missing Number
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Arrays
Statement: Given n distinct numbers from 0..n, return the missing number using
sum or XOR. Sample Input: a = [3, 0, 1] Sample Output: 2 Explanation: 0, 1, 3
are present, so 2 is missing.
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
    int missingNumber(vector<int> &a) {
        int x = 0;
        for (int i = 0; i <= (int)a.size(); i++)
            x ^= i;
        for (int v : a)
            x ^= v;
        return x;
    }
};

int main() {
    vector<int> a = {3, 0, 1};

    Solution sol;
    auto ans = sol.missingNumber(a);
    cout << ans << endl;
    return 0;
}

/*
Approach:
XOR 0..n with array.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Pairs cancel.
*/
