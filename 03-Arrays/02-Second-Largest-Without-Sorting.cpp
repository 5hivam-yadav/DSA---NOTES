/*
Problem: Second Largest without Sorting
Platform: GFG / Striver A2Z
Problem Number: -
Difficulty: Easy
Pattern: Arrays
Statement: Given an integer array, return the second largest distinct element in one pass without sorting.
Sample Input: a = [3, 7, 2, 9, 4]
Sample Output: 7
Explanation: Largest is 9, second largest distinct value is 7.
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

int secondLargest(vector<int>& a) {
    int m1 = INT_MIN, m2 = INT_MIN;
    for (int x : a) {
        if (x > m1) {
            m2 = m1;
            m1 = x;
        }
        else if (x > m2 && x != m1) m2 = x;
    }
    return m2 == INT_MIN ? -1 : m2;
}

int main() {
    vector<int> a = {3, 7, 2, 9, 4};

    auto ans = secondLargest(a);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Track top two.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Two variables.
*/
