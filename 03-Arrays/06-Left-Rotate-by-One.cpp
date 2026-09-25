/*
Problem: Left Rotate by One
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Arrays
Statement: Given an array, rotate it left by one position in place.
Sample Input: a = [1, 2, 3, 4]
Sample Output: [2, 3, 4, 1]
Explanation: The first element moves to the end.
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

void rot1(vector<int>& a) {
    if (a.empty()) return;
    int f = a[0];
    for (size_t i = 1; i < a.size(); i++) a[i - 1] = a[i];
    a.back() = f;
}

int main() {
    vector<int> a = {1, 2, 3, 4};

    rot1(a);
    for (int i = 0; i < (int)a.size(); i++) cout << a[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Save first, shift, place last.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Shift trick.
*/
