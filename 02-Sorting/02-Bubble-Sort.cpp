/*
Problem: Bubble Sort
Platform: GFG / Striver A2Z
Problem Number: -
Difficulty: Easy
Pattern: Sorting
Statement: Sort the array in non-decreasing order in place using bubble sort: repeatedly swap adjacent out-of-order pairs.
Sample Input: arr = [5, 1, 4, 2, 8]
Sample Output: [1,2,4,5,8]
Explanation: Large elements bubble to the end each pass.
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

// Striver A2Z: Bubble Sort
void bubble_sort(vector<int>& arr, int n) {
    for (int i = n - 1; i >= 0; i--) {
        int didSwap = 0;
        for (int j = 0; j <= i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                didSwap = 1;
            }
        }
        if (didSwap == 0) break;
    }
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
1. Bubble max right.
2. Early exit if sorted.
Time Complexity:
O(n^2), best O(n)
Space Complexity:
O(1)
Key Idea:
Adjacent swaps;
adaptive.
*/
