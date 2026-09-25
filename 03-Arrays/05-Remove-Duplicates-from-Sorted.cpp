/*
Problem: Remove Duplicates from Sorted
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Two Pointers
Statement: Given a sorted array, remove duplicates in place and return the new length; the first k entries hold the unique values.
Sample Input: a = [1, 1, 2, 2, 3]
Sample Output: 3
Explanation: Unique values are [1, 2, 3], so k = 3.
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
    int removeDuplicates(vector<int>& a) {
        if (a.empty()) return 0;
        int i = 0;
        for (int j = 1; j < (int)a.size(); j++) if (a[j] != a[i]) a[++i] = a[j];
        return i + 1;
    }
};

int main() {
    vector<int> a = {1, 1, 2, 2, 3};

    Solution sol;
    auto ans = sol.removeDuplicates(a);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Slow/fast overwrite.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
i = unique end.
*/
