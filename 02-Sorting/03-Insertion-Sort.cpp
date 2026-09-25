/*
Problem: Insertion Sort
Platform: GFG / Striver A2Z
Problem Number: -
Difficulty: Easy
Pattern: Sorting
Statement: Sort the array in non-decreasing order in place using insertion sort: insert each element into the sorted prefix.
Sample Input: arr = [12, 11, 13, 5, 6]
Sample Output: [5,6,11,12,13]
Explanation: The left prefix stays sorted as it grows.
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

// Striver A2Z: Insertion Sort
void insertion_sort(vector<int>& arr, int n) {
    for (int i = 0; i <= n - 1; i++) {
        int j = i;
        while (j > 0 && arr[j - 1] > arr[j]) {
            swap(arr[j - 1], arr[j]);
            j--;
        }
    }
}

int main() {
    vector<int> arr = {12, 11, 13, 5, 6};
    int n = arr.size();

    insertion_sort(arr, n);

    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
1. Take a[i].
2. Shift larger right, insert.
Time Complexity:
O(n^2), best O(n)
Space Complexity:
O(1)
Key Idea:
Good nearly sorted.
*/
