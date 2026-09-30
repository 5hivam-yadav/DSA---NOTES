#include <bits/stdc++.h>
using namespace std;

struct MoQuery {
    int left;
    int right; // inclusive
    int id;
};

vector<int> countDistinctInRanges(const vector<int> &values,
                                  const vector<pair<int, int>> &ranges) {
    int n = values.size();
    int q = ranges.size();
    if (q == 0)
        return {};
    vector<int> compressed = values;
    sort(compressed.begin(), compressed.end());
    compressed.erase(unique(compressed.begin(), compressed.end()),
                     compressed.end());

    vector<int> code(n);
    for (int i = 0; i < n; ++i)
        code[i] = lower_bound(compressed.begin(), compressed.end(), values[i]) -
                  compressed.begin();

    int blockSize = max(1, (int)sqrt(max(1, n)));
    vector<MoQuery> queries;
    for (int i = 0; i < q; ++i) {
        auto [left, right] = ranges[i];
        if (left < 0 || right < left || right >= n)
            throw out_of_range("query range");
        queries.push_back({left, right, i});
    }
    sort(queries.begin(), queries.end(),
         [&](const MoQuery &a, const MoQuery &b) {
             int blockA = a.left / blockSize;
             int blockB = b.left / blockSize;
             if (blockA != blockB)
                 return blockA < blockB;
             return blockA & 1 ? a.right > b.right : a.right < b.right;
         });

    vector<int> frequency(compressed.size(), 0);
    vector<int> answer(q);
    int currentLeft = 0;
    int currentRight = -1;
    int distinct = 0;
    auto add = [&](int index) {
        if (frequency[code[index]]++ == 0)
            ++distinct;
    };
    auto remove = [&](int index) {
        if (--frequency[code[index]] == 0)
            --distinct;
    };

    for (const MoQuery &query : queries) {
        while (currentLeft > query.left)
            add(--currentLeft);
        while (currentRight < query.right)
            add(++currentRight);
        while (currentLeft < query.left)
            remove(currentLeft++);
        while (currentRight > query.right)
            remove(currentRight--);
        answer[query.id] = distinct;
    }
    return answer;
}
