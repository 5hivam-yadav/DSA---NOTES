/*
Problem: Leaders in Array
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Arrays
Statement: Given an array, return leaders (elements greater than everything to their right), scanning from the right.
Sample Input: a = [16, 17, 4, 3, 5, 2]
Sample Output: [17, 5, 2]
Explanation: 17, 5 and 2 each beat everything right of them.
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

vector<int> leaders(vector<int>& a) {
    vector<int> r;
    int mx = INT_MIN;
    for (int i = (int)a.size() - 1; i >= 0; i--) {
        if (a[i] > mx) {
            r.push_back(a[i]);
            mx = a[i];
        }
    }
    reverse(r.begin(), r.end());
    return r;
}

int main() {
    vector<int> a = {16, 17, 4, 3, 5, 2};

    auto ans = leaders(a);
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Right-to-left max.
Time Complexity:
O(n)
Space Complexity:
O(k)
Key Idea:
Scan from right.
*/
