#include <bits/stdc++.h>
using namespace std;

vector<int> primesInRange(int left, int right) {
    if (right < left || right < 2)
        return {};
    left = max(left, 2);
    int limit = sqrt(right);
    vector<bool> isPrime(limit + 1, true);
    if (!isPrime.empty())
        isPrime[0] = false;
    if (limit >= 1)
        isPrime[1] = false;
    vector<int> basePrimes;
    for (int p = 2; p <= limit; ++p) {
        if (!isPrime[p])
            continue;
        basePrimes.push_back(p);
        if ((long long)p * p <= limit)
            for (int multiple = p * p; multiple <= limit; multiple += p)
                isPrime[multiple] = false;
    }

    vector<bool> segment(right - left + 1, true);
    for (int prime : basePrimes) {
        long long first =
            max(1LL * prime * prime, ((left + prime - 1LL) / prime) * prime);
        for (long long value = first; value <= right; value += prime)
            segment[value - left] = false;
    }
    vector<int> result;
    for (int i = 0; i < (int)segment.size(); ++i)
        if (segment[i])
            result.push_back(left + i);
    return result;
}
