/*
Problem: N Meetings in One Room
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Greedy
Statement: Given start/end times, return the maximum meetings in one room by sorting on end time.
Sample Input: start = [1,3,0,5,8,5], end = [2,4,6,7,9,9]
Sample Output: 4
Explanation: Four non-overlapping meetings fit.
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

int maxMeet(vector<int>& s, vector<int>& e) {
    vector<pair<int, int>> v;
    for (size_t i = 0; i < s.size(); i++) v.push_back({e[i], s[i]});
    sort(v.begin(), v.end());
    int c = 0, last = -1e9;
    for (auto& p : v) if (p.second > last) {
        c++;
        last = p.first;
    }
    return c;
}

int main() {
    vector<int> start = {1, 3, 0, 5, 8, 5};
    vector<int> end = {2, 4, 6, 7, 9, 9};

    auto ans = maxMeet(start, end);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Sort by end.
Time Complexity:
O(n log n)
Space Complexity:
O(n)
Key Idea:
Earliest end first.
*/
