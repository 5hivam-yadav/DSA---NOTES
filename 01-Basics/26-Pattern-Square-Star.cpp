/*
Problem: Pattern Square Star
Platform: GFG / Striver A2Z
Problem Number: -
Difficulty: Easy
Pattern: Basics
Statement: Given n, print an n x n square of stars (n rows, n stars per row).
Sample Input: n = 3
Sample Output: 3x3 block of '*'
Explanation: Each of 3 rows holds 3 stars.
*/
#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

void printSquare(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << "* ";
        cout << "\n";
    }
}

int main() {
    int n = 3;

    printSquare(n);
    // function returns nothing
    return 0;
}

/*
Approach:
n rows x n cols of stars.
Time Complexity:
O(n^2)
Space Complexity:
O(1)
Key Idea:
Outer rows, inner cols.
*/
