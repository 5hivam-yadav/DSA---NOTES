/*
Problem: Introduction to Bit Manipulation
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Bit Manipulation
Statement: Given n, demonstrate core bit operations: get, set, clear and toggle the k-th bit and count set bits.
Sample Input: n = 13 (1101), k = 1
Sample Output: get=0, set->15, clear->13, toggle->15
Explanation: Bit 1 of 1101 is 0; setting it gives 1111 = 15.
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

int getBit(int n, int k) {
    return (n >> k) & 1;
}
int setBit(int n, int k) {
    return n | (1 << k);
}
int clearBit(int n, int k) {
    return n & ~(1 << k);
}
int toggleBit(int n, int k) {
    return n ^ (1 << k);
}

/*
Approach:
Masks per operation.
Time Complexity:
O(1)
Space Complexity:
O(1)
Key Idea:
AND/OR/XOR masks.
*/
