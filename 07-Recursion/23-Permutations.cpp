/*
Problem: Permutations
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Recursion
Statement: Given distinct numbers, return all orderings via backtracking.
Sample Input: nums = [1,2,3]
Sample Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,2,1],[3,1,2]]
Explanation: 3! = 6 orderings.
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
    vector<vector<int>> ans;
    void f(int i, vector<int>& a) {
        if (i == (int)a.size()) {
            ans.push_back(a);
            return;
        }
        for (int j = i; j < (int)a.size(); j++) {
            swap(a[i], a[j]);
            f(i + 1, a);
            swap(a[i], a[j]);
        }
    }
    vector<vector<int>> permute(vector<int>& a) {
        f(0, a);
        return ans;
    }
};

int main() {
    vector<int> nums = {1, 2, 3};

    Solution sol;
    auto ans = sol.permute(nums);
    for (int i = 0; i < (int)ans.size(); i++) {
        for (int j = 0; j < (int)ans[i].size(); j++) cout << ans[i][j] << " ";
        cout << endl;
    }
    return 0;
}

/*
Approach:
Swap + backtrack.
Time Complexity:
O(n! n)
Space Complexity:
O(n)
Key Idea:
Fix position i.
*/
