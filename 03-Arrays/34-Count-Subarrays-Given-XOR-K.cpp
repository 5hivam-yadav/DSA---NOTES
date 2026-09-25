/*
Problem: Count Subarrays Given XOR K
Platform: LeetCode
Problem Number: -
Difficulty: Medium
Pattern: Bit Manipulation
Statement: Given an array and k, count subarrays with XOR equal to k using prefix XOR and a hashmap.
Sample Input: a = [4, 2, 2, 6, 4], k = 6
Sample Output: 4
Explanation: Four subarrays XOR to 6: [4,2],[2,6,4] and two [6] windows.
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

int xorK(vector<int>& a, int k) {
    unordered_map<int, int> f;
    f[0] = 1;
    int x = 0, c = 0;
    for (int v : a) {
        x ^= v;
        if (f.count(x ^ k)) c += f[x ^ k];
        f[x]++;
    }
    return c;
}

int main() {
    vector<int> a = {4, 2, 2, 6, 4};
    int k = 6;

    auto ans = xorK(a, k);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Prefix XOR freq.
Time Complexity:
O(n) avg
Space Complexity:
O(n)
Key Idea:
need = x^k.
*/
