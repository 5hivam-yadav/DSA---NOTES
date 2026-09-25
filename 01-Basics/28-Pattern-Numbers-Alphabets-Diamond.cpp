/*
Problem: Pattern Numbers Alphabets Diamond
Platform: GFG / Striver A2Z
Problem Number: -
Difficulty: Easy
Pattern: Basics
Statement: Given n, print number triangles, alphabet triangles and a diamond pattern.
Sample Input: n = 3
Sample Output: 1 / 12 / 123 and A / AB / ABC plus diamond
Explanation: Each row extends the sequence; diamond mirrors it.
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

  // 1 / 12 / 123 ...
void numberTriangle(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) cout << j << " ";
        cout << "\n";
    }
}

  // A / AB / ABC ...
void alphaTriangle(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) cout << char('A' + j) << " ";
        cout << "\n";
    }
}

  // 1 / 22 / 333 ...
void repeatNumber(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) cout << i << " ";
        cout << "\n";
    }
}

  // Diamond: pyramid + inverted pyramid
void diamond(int n) {
    for (int i = 0; i < n; i++) {
        for (int s = 0; s < n - i - 1; s++) cout << " ";
        for (int j = 0; j < 2 * i + 1; j++) cout << "* ";
        cout << "\n";
    }
    for (int i = n - 2; i >= 0; i--) {
        for (int s = 0; s < n - i - 1; s++) cout << " ";
        for (int j = 0; j < 2 * i + 1; j++) cout << "* ";
        cout << "\n";
    }
}

int main() {
    int n = 3;

    diamond(n);
    // function returns nothing
    return 0;
}

/*
Approach:
Counters map row->value;
diamond mirrors pyramid.
Time Complexity:
O(n^2)
Space Complexity:
O(1)
Key Idea:
Number/char = f(row, col).
*/
