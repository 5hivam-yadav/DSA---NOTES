/*
Problem: If Else Statements
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Basics
Statement: Given marks m, return the grade: 90+ A, 75+ B, 60+ C, 40+ D, else F.
Sample Input: m = 82
Sample Output: B
Explanation: 82 falls in the 75-89 band, so the grade is B.
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

// Striver A2Z: If-Else ladder
string grade(int marks) {
    if (marks >= 90) return "A";
    else if (marks >= 75) return "B";
    else if (marks >= 60) return "C";
    else if (marks >= 40) return "D";
    else return "F";
}

int main() {
    int marks = 82;

    cout << grade(marks) << endl;
    return 0;
}

/*
Approach:
1. Chain conditions top-down.
2. First true wins.
Time Complexity:
O(1)
Space Complexity:
O(1)
Key Idea:
Order conditions from strictest.
*/
