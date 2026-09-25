/*
Problem: Highest Lowest Frequency
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Hashing
Statement: Given an array, return the elements with the highest and lowest frequency (ties broken by smaller value).
Sample Input: a = [1, 2, 1, 3, 2, 1]
Sample Output: (1, 3)
Explanation: 1 appears most (3x); 3 appears least (1x).
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

pair<int, int> hiLo(vector<int>& a) {
    unordered_map<int, int> f;
    for (int x : a) f[x]++;
    int hi = a[0], lo = a[0];
    for (auto& p : f) {
        if (p.second > f[hi]) hi = p.first;
        if (p.second < f[lo]) lo = p.first;
    }
    return { hi, lo};
}

int main() {
    vector<int> a = {1, 2, 1, 3, 2, 1};

    auto ans = hiLo(a);
    cout << ans.first << " " << ans.second << endl;
    return 0;
}

/*
Approach:
1. Build freq.
2. Track max/min count.
Time Complexity:
O(n) avg
Space Complexity:
O(n)
Key Idea:
One pass count, one pass decide.
*/
