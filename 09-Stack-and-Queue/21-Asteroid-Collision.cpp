/*
Problem: Asteroid Collision
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Monotonic Stack
Statement: Given asteroids (sign = direction, value = size), simulate collisions with a stack; equal sizes destroy both.
Sample Input: asteroids = [5, 10, -5]
Sample Output: [5, 10]
Explanation: 10 survives against -5; 5 never collides.
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
    vector<int> asteroidCollision(vector<int>& a) {
        vector<int> st;
        for (int x : a) {
            bool alive = true;
            while (alive && x < 0 && !st.empty() && st.back() > 0) {
                if (st.back() < -x) {
                    st.pop_back();
                }
                else if (st.back() == -x) {
                    st.pop_back();
                    alive = false;
                }
                else alive = false;
            }
            if (alive) st.push_back(x);
        }
        return st;
    }
};

int main() {
    vector<int> asteroids = {5, 10, -5};

    Solution sol;
    auto ans = sol.asteroidCollision(asteroids);
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Collide + vs -.
Time Complexity:
O(n)
Space Complexity:
O(n)
Key Idea:
Stack survivors.
*/
