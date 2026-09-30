#include <bits/stdc++.h>
using namespace std;

// Minimum Hamiltonian cycle starting/ending at vertex 0; n should be <= 18.
long long travelingSalesman(const vector<vector<long long>> &cost) {
    int n = cost.size();
    if (n == 0)
        return 0;
    if (n > 18)
        throw invalid_argument("bitmask TSP is intended for n <= 18");
    if (n == 1)
        return cost[0][0];

    const long long inf = LLONG_MAX / 4;
    int states = 1 << n;
    vector<vector<long long>> dp(states, vector<long long>(n, inf));
    dp[1][0] = 0;
    for (int mask = 1; mask < states; ++mask) {
        if ((mask & 1) == 0)
            continue;
        for (int last = 0; last < n; ++last) {
            if (dp[mask][last] == inf)
                continue;
            for (int next = 1; next < n; ++next) {
                if ((mask >> next) & 1)
                    continue;
                int nextMask = mask | (1 << next);
                dp[nextMask][next] =
                    min(dp[nextMask][next], dp[mask][last] + cost[last][next]);
            }
        }
    }

    long long answer = inf;
    int full = states - 1;
    for (int last = 1; last < n; ++last)
        answer = min(answer, dp[full][last] + cost[last][0]);
    return answer;
}
