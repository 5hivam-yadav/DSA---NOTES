#include <bits/stdc++.h>
using namespace std;

vector<int> zFunction(const string &s) {
    int n = s.size();
    vector<int> z(n, 0);
    for (int i = 1, left = 0, right = 0; i < n; ++i) {
        if (i <= right)
            z[i] = min(right - i + 1, z[i - left]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > right) {
            left = i;
            right = i + z[i] - 1;
        }
    }
    return z;
}

vector<int> zSearch(const string &text, const string &pattern) {
    if (pattern.empty()) {
        vector<int> matches(text.size() + 1);
        iota(matches.begin(), matches.end(), 0);
        return matches;
    }
    string joined = pattern;
    joined.push_back('\0');
    joined += text;
    vector<int> z = zFunction(joined);
    vector<int> matches;
    for (int i = pattern.size() + 1; i < (int)joined.size(); ++i)
        if (z[i] >= (int)pattern.size())
            matches.push_back(i - pattern.size() - 1);
    return matches;
}
