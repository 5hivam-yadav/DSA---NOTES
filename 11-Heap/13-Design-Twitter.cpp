/*
Problem: Design Twitter
Platform: LeetCode / GFG
Problem Number: -
Difficulty: Medium
Pattern: Heap / Priority Queue
Statement: Design Twitter with postTweet, follow/unfollow and getNewsFeed (latest 10 across followees via max-heap merge).
Sample Input: post 1:5, follow 1->2, post 2:6, feed 1
Sample Output: [6, 5]
Explanation: Feed merges both users newest-first.
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

class Twitter {
    int t = 0;
    unordered_map<int, vector<pair<int, int>>> posts;
    unordered_map<int, unordered_set<int>> fol;
public:
    void postTweet(int u, int id) {
        posts[u].push_back({t++, id});
    }
    vector<int> getNewsFeed(int u) {
        fol[u].insert(u);
        using T = tuple<int, int, int, int>;
        priority_queue<T> pq;
        for (int v : fol[u]) {
            auto& p = posts[v];
            if (!p.empty()) {
                int i = (int)p.size() - 1;
                pq.push({p[i].first, p[i].second, v, i});
            }
        }
        vector<int> r;
        while (!pq.empty() && r.size() < 10) {
            auto [tm, id, v, i] = pq.top();
            pq.pop();
            r.push_back(id);
            if (i > 0) {
                auto& p = posts[v];
                pq.push({p[i-1].first, p[i-1].second, v, i - 1});
            }
        }
        return r;
    }
    void follow(int a, int b) {
        fol[a].insert(b);
    }
    void unfollow(int a, int b) {
        fol[a].erase(b);
    }
};

/*
Approach:
Heap merge feeds.
Time Complexity:
O(F log F)
Space Complexity:
O(posts)
Key Idea:
K-way on timestamps.
*/
