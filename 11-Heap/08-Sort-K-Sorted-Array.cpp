/*
Problem: Sort K Sorted Array
Platform: GFG / Striver A2Z
Problem Number: -
Difficulty: Easy
Pattern: Heap / Priority Queue
Statement: Given a k-sorted array (each element at most k away), sort it with a min-heap of size k+1.
Sample Input: a = [6,5,3,2,8,10,9], k = 3
Sample Output: [2,3,5,6,8,9,10]
Explanation: Heap always fixes the next smallest.
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

vector<int> sortK(vector<int>& a, int k) {
    priority_queue<int, vector<int>, greater<int>> pq;
    vector<int> r;
    for (int x : a) {
        pq.push(x);
        if ((int)pq.size() > k) {
            r.push_back(pq.top());
            pq.pop();
        }
    }
    while (!pq.empty()) {
        r.push_back(pq.top());
        pq.pop();
    }
    return r;
}

int main() {
    vector<int> a = {6, 5, 3, 2, 8, 10, 9};
    int k = 3;

    auto ans = sortK(a, k);
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Window heap k+1.
Time Complexity:
O(n log k)
Space Complexity:
O(k)
Key Idea:
Each element within k.
*/
