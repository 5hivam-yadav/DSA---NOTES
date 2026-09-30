/*
Problem: Move Zeros to End
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Arrays
Statement: Given an array, move all zeros to the end while keeping the relative
order of non-zero elements. Sample Input: a = [0, 1, 0, 3, 12] Sample Output:
[1, 3, 12, 0, 0] Explanation: Non-zeros keep order, zeros shift right.
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
    void moveZeroes(vector<int> &a) {
        int i = 0;
        for (int x : a)
            if (x != 0)
                a[i++] = x;
        while (i < (int)a.size())
            a[i++] = 0;
    }
};

int main() {
    vector<int> a = {0, 1, 0, 3, 12};

    Solution sol;
    sol.moveZeroes(a);
    for (int i = 0; i < (int)a.size(); i++)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Compact then fill.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Stable partition.
*/
