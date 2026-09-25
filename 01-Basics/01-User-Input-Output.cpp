/*
Problem: User Input Output
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Basics
Statement: Read two integers from standard input and print their sum. Use fast I/O for all programs.
Sample Input: 3 4
Sample Output: 7
Explanation: 3 + 4 = 7.
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, y;
    cin >> x >> y;
    cout << x + y << "\n";
    return 0;
}

/*
Approach:
1. Fast I/O lines.
2. Read with cin.
3. Print with cout.
Time Complexity:
O(1)
Space Complexity:
O(1)
Key Idea:
cin/cout with fast-io for all problems.
*/
