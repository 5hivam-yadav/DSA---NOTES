#include <bits/stdc++.h>
using namespace std;

// Stable counting sort for integer ranges whose width is safe to allocate.
vector<int> countingSort(const vector<int> &values) {
    if (values.empty())
        return {};
    auto [minimum, maximum] = minmax_element(values.begin(), values.end());
    size_t range = (size_t)((long long)*maximum - *minimum + 1);
    vector<size_t> count(range, 0);
    for (int value : values)
        ++count[(size_t)((long long)value - *minimum)];

    vector<int> sorted;
    sorted.reserve(values.size());
    for (size_t offset = 0; offset < range; ++offset) {
        for (size_t remaining = count[offset]; remaining > 0; --remaining)
            sorted.push_back((int)((long long)*minimum + offset));
    }
    return sorted;
}
