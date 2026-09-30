/*
Problem: Connect Ropes Min Cost
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Heap / Priority Queue
Statement: Given rope lengths, connect them with minimum total cost (always join
two shortest; Huffman-style heap). Sample Input: a = [4,3,2,6] Sample Output: 29
Explanation: 2+3=5, 4+5=9, 6+9=15; total 5+9+15 = 29.
*/
#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

long long minCost(vector<int> &a) {
    priority_queue<long long, vector<long long>, greater<long long>> pq(
        a.begin(), a.end());
    long long c = 0;
    while (pq.size() > 1) {
        long long x = pq.top();
        pq.pop();
        long long y = pq.top();
        pq.pop();
        c += x + y;
        pq.push(x + y);
    }
    return c;
}

int main() {
    vector<int> a = {4, 3, 2, 6};

    auto ans = minCost(a);
    cout << ans << endl;
    return 0;
}

/*
Approach:
Always merge smallest.
Time Complexity:
O(n log n)
Space Complexity:
O(n)
Key Idea:
Huffman greedy.
*/
