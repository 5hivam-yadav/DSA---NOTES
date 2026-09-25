/*
Problem: Arrays and Strings
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Basics
Statement: Given an integer array, return its sum; given a string, return its reverse. Covers basic array and string traversal.
Sample Input: a = [1, 2, 3], s = "abc"
Sample Output: 6, "cba"
Explanation: 1+2+3 = 6 and "abc" reversed is "cba".
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

int arrSum(vector<int>& a) {
    int s = 0;
    for (int x : a) s += x;
    return s;
}
string revStr(string s) {
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    vector<int> a = {1, 2, 3};
    string s = "abc";

    auto ans = revStr(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
1. Range-for over vector.
2. reverse() on string.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
vector + string are the default containers.
*/
