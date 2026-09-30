/*
Problem: Count Subarrays Sum K
Platform: LeetCode
Problem Number: -
Difficulty: Easy
Pattern: Arrays
Statement: Given an array and k, count the subarrays summing to k with prefix
sums and a hashmap. Sample Input: a = [1, 1, 1], k = 2 Sample Output: 2
Explanation: Subarrays [1, 1] at (0,1) and (1,2) both sum to 2.
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
    int subarraySum(vector<int> &a, int k) {
        unordered_map<long long, int> f;
        f[0] = 1;
        long long s = 0;
        int c = 0;
        for (int x : a) {
            s += x;
            if (f.count(s - k))
                c += f[s - k];
            f[s]++;
        }
        return c;
    }
};

int main() {
    vector<int> a = {1, 1, 1};
    int k = 2;

    Solution sol;
    auto ans = sol.subarraySum(a, k);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Prefix freq.
Time Complexity:
O(n) avg
Space Complexity:
O(n)
Key Idea:
s - k lookup.
*/
