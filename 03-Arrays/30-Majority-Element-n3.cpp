/*
Problem: Majority Element n/3
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Hashing
Statement: Given an array of size n, return all elements appearing more than n/3 times (at most two; extended Boyer-Moore).
Sample Input: nums = [3, 2, 3]
Sample Output: [3]
Explanation: 3 appears twice, more than 3/3 = 1.
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
    vector<int> majorityElement(vector<int>& a) {
        int c1 = 0, c2 = 0, e1 = 0, e2 = 1;
        for (int x : a) {
            if (x == e1) c1++;
            else if (x == e2) c2++;
            else if (c1 == 0) {
                e1 = x;
                c1 = 1;
            }
            else if (c2 == 0) {
                e2 = x;
                c2 = 1;
            }
            else {
                c1--;
                c2--;
            }
        }
        c1 = c2 = 0;
        for (int x : a) {
            if (x == e1) c1++;
            else if (x == e2) c2++;
        }
        vector<int> r;
        int n = a.size();
        if (c1 > n / 3) r.push_back(e1);
        if (c2 > n / 3) r.push_back(e2);
        return r;
    }
};

int main() {
    vector<int> nums = {3, 2, 3};

    Solution sol;
    auto ans = sol.majorityElement(nums);
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Two candidates + verify.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Extended Moore.
*/
