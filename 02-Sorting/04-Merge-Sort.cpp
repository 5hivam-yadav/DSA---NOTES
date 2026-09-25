/*
Problem: Merge Sort
Platform: GFG / Striver A2Z
Problem Number: -
Difficulty: Medium
Pattern: Sorting
Statement: Sort the array in non-decreasing order using merge sort: split recursively, merge sorted halves.
Sample Input: arr = [38, 27, 43, 3, 9, 82, 10]
Sample Output: [3,9,10,27,38,43,82]
Explanation: Halves sort recursively then merge linearly.
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

// Striver A2Z: Merge Sort
void merge(vector<int>& arr, int low, int mid, int high) {
    vector<int> temp;
    int left = low, right = mid + 1;

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) temp.push_back(arr[left++]);
        else temp.push_back(arr[right++]);
    }
    while (left <= mid) temp.push_back(arr[left++]);
    while (right <= high) temp.push_back(arr[right++]);

    for (int i = low; i <= high; i++) arr[i] = temp[i - low];
}

void ms(vector<int>& arr, int low, int high) {
    if (low >= high) return;
    int mid = (low + high) / 2;
    ms(arr, low, mid);
    ms(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

void mergeSort(vector<int>& arr, int n) {
    ms(arr, 0, n - 1);
}

int main() {
    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};
    int n = arr.size();

    mergeSort(arr, n);

    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
1. Split half.
2. Sort halves.
3. Merge.
Time Complexity:
O(n log n)
Space Complexity:
O(n)
Key Idea:
Stable divide-conquer.
*/
