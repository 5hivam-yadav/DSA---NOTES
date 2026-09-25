/*
Problem: Recursive Bubble Sort
Platform: GFG / Striver A2Z
Problem Number: -
Difficulty: Easy
Pattern: Sorting
Statement: Sort the array using recursive bubble sort: one bubble pass, then recurse on the first n-1 elements.
Sample Input: arr = [5, 1, 4, 2, 8]
Sample Output: [1,2,4,5,8]
Explanation: Each call bubbles the largest to the end.
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

// Striver A2Z: Recursive Bubble Sort
void bubble_sort(vector<int>& arr, int n) {
    if (n == 1) return;
    for (int j = 0; j <= n - 2; j++) {
        if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
    }
    bubble_sort(arr, n - 1);
}

int main() {
    vector<int> arr = {5, 1, 4, 2, 8};
    int n = arr.size();

    bubble_sort(arr, n);

    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
1. One pass max to end.
2. Recurse n-1.
Time Complexity:
O(n^2)
Space Complexity:
O(n) stack
Key Idea:
Recursion replaces outer loop.
*/
