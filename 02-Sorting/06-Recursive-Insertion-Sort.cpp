/*
Problem: Recursive Insertion Sort
Platform: GFG / Striver A2Z
Problem Number: -
Difficulty: Easy
Pattern: Sorting
Statement: Sort the array using recursive insertion sort: sort first n-1, then insert the last element into place.
Sample Input: arr = [12, 11, 13, 5, 6]
Sample Output: [5,6,11,12,13]
Explanation: Recursion sorts the prefix before inserting.
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

// Striver A2Z: Recursive Insertion Sort
void insertion_sort(vector<int>& arr, int i, int n) {
    if (i == n) return;
    int j = i;
    while (j > 0 && arr[j - 1] > arr[j]) {
        int temp = arr[j - 1];
        arr[j - 1] = arr[j];
        arr[j] = temp;
        j--;
    }
    insertion_sort(arr, i + 1, n);
}

int main() {
    vector<int> arr = {12, 11, 13, 5, 6};
    int n = arr.size();

    insertion_sort(arr, 0, n);

    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
1. Insert a[i].
2. Recurse i+1.
Time Complexity:
O(n^2)
Space Complexity:
O(n) stack
Key Idea:
Recursion replaces outer loop.
*/
