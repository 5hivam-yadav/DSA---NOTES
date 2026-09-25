/*
Problem: Switch Statement
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Basics
Statement: Given day number d (1-7), return the weekday name starting Monday; return Invalid for other values.
Sample Input: d = 3
Sample Output: Wednesday
Explanation: Day 3 maps to Wednesday.
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

// Striver A2Z: Switch case
string dayName(int day) {
    switch (day) {
        case 1: return "Monday";
        case 2: return "Tuesday";
        case 3: return "Wednesday";
        case 4: return "Thursday";
        case 5: return "Friday";
        case 6: return "Saturday";
        case 7: return "Sunday";
        default: return "Invalid";
    }
}

int main() {
    int day = 3;

    cout << dayName(day) << endl;
    return 0;
}

/*
Approach:
1. Match case.
2. Default fallback.
3. Break/return each case.
Time Complexity:
O(1)
Space Complexity:
O(1)
Key Idea:
Switch dispatches on constant value.
*/
