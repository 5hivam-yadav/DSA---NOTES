/*
Problem: Number of NGEs
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Stack and Queue
Statement: Given an array and a list of query indices, return the count of next greater elements to the right of each queried index (pair the sorted queries with a BIT for large inputs).
Sample Input: a = [3,4,2,7,5], queries = [0, 1]
Sample Output: [3, 1]
Explanation: Right of a[0]=3 sit 4,2,7,5 with 3 values greater; right of a[1]=4 only 7 is greater.
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

vector<int> ngeCount(vector<int>& a, vector<int>& qi) {
    vector<int> r;
    for (int i : qi) {
        int c = 0;
        for (size_t j = i + 1; j < a.size(); j++) if (a[j] > a[i]) c++;
        r.push_back(c);
    }
    return r;
}
  // Offline BIT O((n+q) log n) for large q.

int main() {
    vector<int> a = {3, 4, 2, 7, 5};
    vector<int> queries = {0, 1};

    auto ans = ngeCount(a, queries);
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Brute per query.
Time Complexity:
O(nq)
Space Complexity:
O(1)
Key Idea:
BIT for scale.
*/
