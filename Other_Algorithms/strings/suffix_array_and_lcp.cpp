#include <bits/stdc++.h>
using namespace std;

vector<int> suffixArray(const string &s) {
    int n = s.size();
    vector<int> order(n), rank(n), nextRank(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return s[a] < s[b]; });
    for (int i = 0; i < n; ++i)
        rank[order[i]] =
            (i > 0 && s[order[i]] == s[order[i - 1]]) ? rank[order[i - 1]] : i;

    for (int length = 1; length < n; length *= 2) {
        auto lessSuffix = [&](int a, int b) {
            if (rank[a] != rank[b])
                return rank[a] < rank[b];
            int rankA = a + length < n ? rank[a + length] : -1;
            int rankB = b + length < n ? rank[b + length] : -1;
            return rankA < rankB;
        };
        sort(order.begin(), order.end(), lessSuffix);
        nextRank[order[0]] = 0;
        for (int i = 1; i < n; ++i)
            nextRank[order[i]] =
                nextRank[order[i - 1]] + lessSuffix(order[i - 1], order[i]);
        rank.swap(nextRank);
        if (rank[order.back()] == n - 1)
            break;
    }
    return order;
}

// lcp[i] is the LCP of suffixes at suffixArray[i] and suffixArray[i-1].
vector<int> kasaiLcp(const string &s, const vector<int> &suffixes) {
    int n = s.size();
    vector<int> position(n), lcp(n, 0);
    for (int i = 0; i < n; ++i)
        position[suffixes[i]] = i;

    for (int start = 0, common = 0; start < n; ++start) {
        int order = position[start];
        if (order == 0)
            continue;
        int previous = suffixes[order - 1];
        while (start + common < n && previous + common < n &&
               s[start + common] == s[previous + common])
            ++common;
        lcp[order] = common;
        if (common > 0)
            --common;
    }
    return lcp;
}
