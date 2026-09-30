/*
Problem: Hands of Straights
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Heap / Priority Queue
Statement: Given hand cards and groupSize, return true if they split into groups
of consecutive values (map + min-heap). Sample Input: hand =
[1,2,3,6,2,3,4,7,8], groupSize = 3 Sample Output: true Explanation: Groups
[1,2,3],[2,3,4],[6,7,8] work.
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

class Solution {
  public:
    bool isNStraightHand(vector<int> &h, int g) {
        map<int, int> f;
        for (int x : h)
            f[x]++;
        for (auto &p : f) {
            while (p.second > 0) {
                for (int i = 0; i < g; i++) {
                    if (f[p.first + i] < p.second)
                        return false;
                    f[p.first + i] -= p.second;
                }
                p.second = 0;
            }
        }
        return true;
    }
};

int main() {
    vector<int> hand = {1, 2, 3, 6, 2, 3, 4, 7, 8};
    int groupSize = 3;

    Solution sol;
    auto ans = sol.isNStraightHand(hand, groupSize);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
Chain from smallest.
Time Complexity:
O(n log n)
Space Complexity:
O(n)
Key Idea:
Greedy consecutive.
*/
