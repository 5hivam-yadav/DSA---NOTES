/*
Problem: All Divisors
Platform: GFG / Striver A2Z
Problem Number: -
Difficulty: Easy
Pattern: Bit Manipulation
Statement: Given n, return all its divisors in ascending order by checking pairs up to sqrt(n).
Sample Input: n = 36
Sample Output: [1, 2, 3, 4, 6, 9, 12, 18, 36]
Explanation: Each value divides 36 evenly.
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

vector<int> divisors(int n) {
    vector<int> v;
    for (int i = 1; 1LL * i * i <= n; i++) if (n % i == 0) {
        v.push_back(i);
        if (i != n / i) v.push_back(n / i);
    }
    sort(v.begin(), v.end());
    return v;
}

int main() {
    int n = 36;

    auto ans = divisors(n);
    for (int i = 0; i < (int)ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Pair push to sqrt.
Time Complexity:
O(sqrt n)
Space Complexity:
O(k)
Key Idea:
Divisor pairs.
*/
