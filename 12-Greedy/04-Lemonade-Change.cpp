/*
Problem: Lemonade Change
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Greedy
Statement: Given bills 5/10/20 in order, return true if correct change can always be given (greedy: prefer 10+5 for 20s).
Sample Input: bills = [5,5,5,10,20]
Sample Output: true
Explanation: Change succeeds at every step.
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

class Solution {
public:
    bool lemonadeChange(vector<int>& b) {
        int f = 0, t = 0;
        for (int x : b) {
            if (x == 5) f++;
            else if (x == 10) {
                if (!f) return false;
                f--;
                t++;
            }
            else {
                if (t > 0 && f > 0) {
                    t--;
                    f--;
                }
                else if (f >= 3) f -= 3;
                else return false;
            }
        }
        return true;
    }
};

int main() {
    vector<int> bills = {5, 5, 5, 10, 20};

    Solution sol;
    auto ans = sol.lemonadeChange(bills);
    cout << (ans ? "true" : "false") << endl;
    return 0;
}

/*
Approach:
Prefer 10+5 for 20.
Time Complexity:
O(n)
Space Complexity:
O(1)
Key Idea:
Use big bills first.
*/
