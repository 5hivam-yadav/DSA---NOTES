/*
Problem: Minimum Platforms
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Greedy
Statement: Given arrival/departure times, return the minimum platforms so no train waits (two-pointer on sorted times).
Sample Input: arr = [900,940,950], dep = [910,1200,1120]
Sample Output: 2
Explanation: Two trains overlap, needing 2 platforms.
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

int platforms(vector<int>& a, vector<int>& d) {
    sort(a.begin(), a.end());
    sort(d.begin(), d.end());
    int i = 0, j = 0, c = 0, b = 0, n = a.size();
    while (i < n && j < n) {
        if (a[i] <= d[j]) {
            c++;
            b = max(b, c);
            i++;
        }
        else {
            c--;
            j++;
        }
    }
    return b;
}

int main() {
    vector<int> arr = {900, 940, 950};
    vector<int> dep = {910, 1200, 1120};

    auto ans = platforms(arr, dep);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Two sorted sweeps.
Time Complexity:
O(n log n)
Space Complexity:
O(1)
Key Idea:
Arrive vs depart.
*/
