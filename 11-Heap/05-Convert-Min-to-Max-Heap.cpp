/*
Problem: Convert Min to Max Heap
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Heap / Priority Queue
Statement: Given a min-heap array, convert it to a max-heap in place by heapifying non-leaf nodes bottom-up.
Sample Input: a = [1, 3, 5, 7, 9]
Sample Output: [9, 7, 5, 1, 3] (valid max-heap)
Explanation: Every parent becomes >= its children.
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

void down(vector<int>& h, int i) {
    int n = h.size();
    while (1) {
        int l = 2*i+1, r = 2*i+2, s = i;
        if (l < n && h[l] > h[s]) s = l;
        if (r < n && h[r] > h[s]) s = r;
        if (s == i) break;
        swap(h[i], h[s]);
        i = s;
    }
}
void minToMax(vector<int>& h) {
    for (int i = (int)h.size()/2 - 1; i >= 0; i--) down(h, i);
}

int main() {
    vector<int> a = {1, 3, 5, 7, 9};

    minToMax(a);
    for (int i = 0; i < (int)a.size(); i++) cout << a[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Bottom-up heapify.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Heapify from last parent.
*/
