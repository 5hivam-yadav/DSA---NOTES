#include <bits/stdc++.h>
using namespace std;

// LSD radix sort for unsigned 32-bit integers.
void radixSort(vector<uint32_t> &values) {
    constexpr int radix = 256;
    vector<uint32_t> buffer(values.size());
    for (int shift = 0; shift < 32; shift += 8) {
        array<size_t, radix> count{};
        for (uint32_t value : values)
            ++count[(value >> shift) & 0xFF];
        for (int i = 1; i < radix; ++i)
            count[i] += count[i - 1];
        for (int i = (int)values.size() - 1; i >= 0; --i) {
            int digit = (values[i] >> shift) & 0xFF;
            buffer[--count[digit]] = values[i];
        }
        values.swap(buffer);
    }
}
