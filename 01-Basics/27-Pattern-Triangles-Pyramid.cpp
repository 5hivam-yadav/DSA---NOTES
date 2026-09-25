/*
Problem: Pattern Triangles Pyramid
Platform: GFG / Striver A2Z
Problem Number: -
Difficulty: Easy
Pattern: Basics
Statement: Given n, print right triangle, inverted triangle and pyramid star patterns (nested loops over rows and columns).
Sample Input: n = 3
Sample Output: right triangle / inverted / pyramid of height 3
Explanation: Row i holds i stars (pyramid centres them).
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

  // Right triangle: *, **, ***, ...
void rightTriangle(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) cout << "* ";
        cout << "\n";
    }
}

  // Inverted triangle: *****, ****, ...
void invertedTriangle(int n) {
    for (int i = n; i >= 1; i--) {
        for (int j = 0; j < i; j++) cout << "* ";
        cout << "\n";
    }
}

  // Pyramid: spaces + odd stars
void pyramid(int n) {
    for (int i = 0; i < n; i++) {
        for (int s = 0; s < n - i - 1; s++) cout << " ";
        for (int j = 0; j < 2 * i + 1; j++) cout << "* ";
        cout << "\n";
    }
}

int main() {
    int n = 3;

    pyramid(n);
    // function returns nothing
    return 0;
}

/*
Approach:
Row i controls stars/spaces counts.
Time Complexity:
O(n^2)
Space Complexity:
O(1)
Key Idea:
Stars = i, spaces = n-i-1, pyramid stars = 2*i+1.
*/
