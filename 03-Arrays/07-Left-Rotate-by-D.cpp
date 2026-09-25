/*
Problem: Left Rotate by D
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Arrays
Statement: Given an array and k, rotate it left by k positions in place (use k %= n and the triple-reverse trick).
Sample Input: a = [1, 2, 3, 4, 5], k = 2
Sample Output: [3, 4, 5, 1, 2]
Explanation: The first two elements move to the end.
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
    void rotate(vector<int>& a, int k) {
        int n = a.size();
        if (!n) return;
        k %= n;
        reverse(a.begin(), a.end());
        reverse(a.begin(), a.begin() + k);
        reverse(a.begin() + k, a.end());
    }
};

int main() {
    vector<int> a = {1, 2, 3, 4, 5};
    int k = 2;

    Solution sol;
    sol.rotate(a, k);
    for (int i = 0; i < (int)a.size(); i++) cout << a[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
k%=n;
3 reverses.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Reversal trick.
*/
