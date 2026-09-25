/*
Problem: Quick Sort
Platform: GFG / Striver A2Z
Problem Number: -
Difficulty: Easy
Pattern: Sorting
Statement: Sort the array in non-decreasing order in place using quick sort: partition around a pivot, recurse both sides.
Sample Input: arr = [10, 7, 8, 9, 1, 5]
Sample Output: [1,5,7,8,9,10]
Explanation: Pivot lands finally, then both sides sort.
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

// Striver A2Z: Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    int i = low, j = high;

    while (i < j) {
        while (arr[i] <= pivot && i <= high - 1) i++;
        while (arr[j] > pivot && j >= low + 1) j--;
        if (i < j) swap(arr[i], arr[j]);
    }
    swap(arr[low], arr[j]);
    return j;
}

void qs(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pIndex = partition(arr, low, high);
        qs(arr, low, pIndex - 1);
        qs(arr, pIndex + 1, high);
    }
}

void quickSort(vector<int>& arr, int n) {
    qs(arr, 0, n - 1);
}

int main() {
    vector<int> arr = {10, 7, 8, 9, 1, 5};
    int n = arr.size();

    quickSort(arr, n);

    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
1. Partition <= pivot.
2. Recurse sides.
Time Complexity:
Avg O(n log n), worst O(n^2)
Space Complexity:
O(log n) stack
Key Idea:
In-place;
random pivot avoids worst.
*/
