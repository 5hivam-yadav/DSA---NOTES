#include <bits/stdc++.h>
using namespace std;

vector<int> buildLps(const string &pattern) {
    vector<int> lps(pattern.size(), 0);
    for (int i = 1, matched = 0; i < (int)pattern.size();) {
        if (pattern[i] == pattern[matched]) {
            lps[i++] = ++matched;
        } else if (matched > 0) {
            matched = lps[matched - 1];
        } else {
            lps[i++] = 0;
        }
    }
    return lps;
}

vector<int> kmpSearch(const string &text, const string &pattern) {
    if (pattern.empty()) {
        vector<int> matches(text.size() + 1);
        iota(matches.begin(), matches.end(), 0);
        return matches;
    }

    vector<int> lps = buildLps(pattern);
    vector<int> matches;
    for (int i = 0, j = 0; i < (int)text.size();) {
        if (text[i] == pattern[j]) {
            ++i;
            ++j;
            if (j == (int)pattern.size()) {
                matches.push_back(i - j);
                j = lps[j - 1];
            }
        } else if (j > 0) {
            j = lps[j - 1];
        } else {
            ++i;
        }
    }
    return matches;
}
