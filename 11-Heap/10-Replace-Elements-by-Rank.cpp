/*
Problem: Replace Elements by Rank
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Easy
Pattern: Heap
Statement: Given an array, replace each element by its rank among distinct
values (compress coordinates). Sample Input: a = [40,10,20,30] Sample Output:
[4,1,2,3] Explanation: Sorted distinct are 10,20,30,40 mapping to 1..4.
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

vector<int> rankify(vector<int> &a) {
    vector<int> s = a;
    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());
    unordered_map<int, int> r;
    for (int i = 0; i < (int)s.size(); i++)
        r[s[i]] = i + 1;
    vector<int> o;
    for (int x : a)
        o.push_back(r[x]);
    return o;
}

int main() {
    vector<int> a = {40, 10, 20, 30};

    auto ans = rankify(a);
    for (int i = 0; i < (int)ans.size(); i++)
        cout << ans[i] << " ";
    cout << endl;
    return 0;
}

/*
Approach:
Sort unique + map.
Time Complexity:
O(n log n)
Space Complexity:
O(n)
Key Idea:
Coordinate rank.
*/
