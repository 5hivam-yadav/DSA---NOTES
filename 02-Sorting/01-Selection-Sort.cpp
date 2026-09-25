/*
Problem: Selection Sort
Platform: GFG / Striver A2Z
Problem Number: -
Difficulty: Easy
Pattern: Sorting
Statement: Sort the array in non-decreasing order in place using selection sort: repeatedly move the suffix minimum forward.
Sample Input: arr = [64, 25, 12, 22, 11]
Sample Output: [11,12,22,25,64]
Explanation: Each pass fixes the next smallest element.
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

// Striver A2Z: Selection Sort
void selection_sort(vector<int>& arr, int n) {
    for (int i = 0; i <= n - 2; i++) {
        int mini = i;
        for (int j = i + 1; j <= n - 1; j++) {
            if (arr[j] < arr[mini]) mini = j;
        }
        swap(arr[mini], arr[i]);
    }
}

int main() {
    vector<int> arr = {64, 25, 12, 22, 11};
    int n = arr.size();

    selection_sort(arr, n);

    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
1. Find min in suffix.
2. Swap to front.
Time Complexity:
O(n^2)
Space Complexity:
O(1)
Key Idea:
Min swaps O(n).
*/
