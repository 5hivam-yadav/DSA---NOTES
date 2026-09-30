#include <bits/stdc++.h>
using namespace std;

class AhoCorasick {
    struct Node {
        array<int, 26> next;
        int link = 0;
        vector<int> output;
        Node() { next.fill(-1); }
    };

    vector<Node> trie{1};
    vector<int> patternLength;
    bool built = false;

  public:
    int addPattern(const string &pattern) {
        if (built)
            throw logic_error("Add patterns before build().");
        if (pattern.empty())
            throw invalid_argument("Patterns must be non-empty.");
        int node = 0;
        for (char ch : pattern) {
            int c = ch - 'a';
            if (c < 0 || c >= 26)
                throw invalid_argument("Patterns must contain lowercase a-z.");
            if (trie[node].next[c] == -1) {
                trie[node].next[c] = trie.size();
                trie.emplace_back();
            }
            node = trie[node].next[c];
        }
        int id = patternLength.size();
        patternLength.push_back(pattern.size());
        trie[node].output.push_back(id);
        return id;
    }

    void build() {
        if (built)
            return;
        queue<int> q;
        for (int c = 0; c < 26; ++c) {
            int child = trie[0].next[c];
            if (child == -1)
                trie[0].next[c] = 0;
            else {
                trie[child].link = 0;
                q.push(child);
            }
        }

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            int suffix = trie[node].link;
            trie[node].output.insert(trie[node].output.end(),
                                     trie[suffix].output.begin(),
                                     trie[suffix].output.end());
            for (int c = 0; c < 26; ++c) {
                int child = trie[node].next[c];
                if (child == -1) {
                    trie[node].next[c] = trie[suffix].next[c];
                } else {
                    trie[child].link = trie[suffix].next[c];
                    q.push(child);
                }
            }
        }
        built = true;
    }

    vector<pair<int, int>> search(const string &text) const {
        if (!built)
            throw logic_error("Call build() before search().");
        vector<pair<int, int>> matches;
        int node = 0;
        for (int i = 0; i < (int)text.size(); ++i) {
            int c = text[i] - 'a';
            if (c < 0 || c >= 26) {
                node = 0;
                continue;
            }
            node = trie[node].next[c];
            for (int id : trie[node].output)
                matches.push_back({i - patternLength[id] + 1, id});
        }
        return matches;
    }
};
