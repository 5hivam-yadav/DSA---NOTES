/*
Problem: Check Array Represents Min Heap
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Heap / Priority Queue
Statement: Given an array, return true if it satisfies the min-heap property a[i] <= a[2i+1], a[2i+2] for all i.
Sample Input: a = [1, 3, 5, 7, 9]
Sample Output: true
Explanation: Every parent is <= its children.
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

bool isMinHeap(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        int l = 2*i+1, r = 2*i+2;
        if (l < n && a[i] > a[l]) return false;
        if (r < n && a[i] > a[r]) return false;
    }
    return true;
}

int main() {
    vector<int> a = {1, 3, 5, 7, 9};

    auto ans = isMinHeap(a);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
Parent <= children.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Heap property scan.
*/
