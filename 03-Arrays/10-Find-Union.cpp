/*
Problem: Find Union
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Arrays
Statement: Given two sorted arrays, return their union as a sorted list of distinct elements.
Sample Input: a = [1, 2, 3], b = [2, 3, 4]
Sample Output: [1, 2, 3, 4]
Explanation: Duplicates across arrays appear once.
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

vector<int> uni(vector<int>& a, vector<int>& b) {
    vector<int> r;
    size_t i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j]) {
            if (r.empty() || r.back() != a[i]) r.push_back(a[i]);
            i++;
        }
        else if (b[j] < a[i]) {
            if (r.empty() || r.back() != b[j]) r.push_back(b[j]);
            j++;
        }
        else {
            if (r.empty() || r.back() != a[i]) r.push_back(a[i]);
            i++;
            j++;
        }
    }
    while (i < a.size()) {
        if (r.empty() || r.back() != a[i]) r.push_back(a[i]);
        i++;
    }
    while (j < b.size()) {
        if (r.empty() || r.back() != b[j]) r.push_back(b[j]);
        j++;
    }
    return r;
}

int main() {
    vector<int> a = {1, 2, 3};
    vector<int> b = {2, 3, 4};

    auto ans = uni(a, b);
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Merge walk + dedup.
Time Complexity:
O(n+m)
Space Complexity:
O(n+m)
Key Idea:
Sorted merge.
*/
