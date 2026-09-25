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

void printSquare(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << "* ";
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
