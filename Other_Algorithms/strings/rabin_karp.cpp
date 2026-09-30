#include <bits/stdc++.h>
using namespace std;

vector<int> rabinKarpSearch(const string &text, const string &pattern) {
    const long long mod = 1'000'000'007;
    const long long base = 257;
    int n = text.size();
    int m = pattern.size();
    if (m == 0) {
        vector<int> matches(n + 1);
        iota(matches.begin(), matches.end(), 0);
        return matches;
    }
    if (m > n)
        return {};

    long long highPower = 1;
    for (int i = 1; i < m; ++i)
        highPower = highPower * base % mod;

    long long patternHash = 0;
    long long windowHash = 0;
    for (int i = 0; i < m; ++i) {
        patternHash =
            (patternHash * base + (unsigned char)pattern[i] + 1) % mod;
        windowHash = (windowHash * base + (unsigned char)text[i] + 1) % mod;
    }

    vector<int> matches;
    for (int start = 0; start + m <= n; ++start) {
        if (patternHash == windowHash && text.compare(start, m, pattern) == 0)
            matches.push_back(start);
        if (start + m == n)
            break;

        long long outgoing =
            ((unsigned char)text[start] + 1LL) * highPower % mod;
        windowHash = (windowHash - outgoing + mod) % mod;
        windowHash =
            (windowHash * base + (unsigned char)text[start + m] + 1) % mod;
    }
    return matches;
}
