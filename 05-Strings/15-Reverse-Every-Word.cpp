/*
Problem: Reverse Every Word
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Strings
Statement: Given a string, reverse the characters of each word while keeping word order.
Sample Input: s = "Hello World"
Sample Output: "olleH dlroW"
Explanation: Each word is individually reversed.
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
#include <sstream>
using namespace std;

string revWords(string s) {
    stringstream ss(s);
    string w, r;
    while (ss >> w) {
        reverse(w.begin(), w.end());
        if (!r.empty()) r += ' ';
        r += w;
    }
    return r;
}

int main() {
    string s = "Hello World";

    auto ans = revWords(s);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Split + reverse each.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Word-wise reverse.
*/
