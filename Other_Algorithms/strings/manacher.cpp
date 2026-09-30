#include <bits/stdc++.h>
using namespace std;

struct PalindromeResult {
    int start;
    int length;
};

PalindromeResult longestPalindrome(const string &s) {
    int n = s.size();
    if (n == 0)
        return {0, 0};

    vector<int> odd(n), even(n);
    int left = 0;
    int right = -1;
    for (int i = 0; i < n; ++i) {
        int radius =
            (i > right) ? 1 : min(odd[left + right - i], right - i + 1);
        while (i - radius >= 0 && i + radius < n &&
               s[i - radius] == s[i + radius])
            ++radius;
        odd[i] = radius;
        if (i + radius - 1 > right) {
            left = i - radius + 1;
            right = i + radius - 1;
        }
    }

    left = 0;
    right = -1;
    for (int i = 0; i < n; ++i) {
        int radius =
            (i > right) ? 0 : min(even[left + right - i + 1], right - i + 1);
        while (i - radius - 1 >= 0 && i + radius < n &&
               s[i - radius - 1] == s[i + radius])
            ++radius;
        even[i] = radius;
        if (i + radius - 1 > right) {
            left = i - radius;
            right = i + radius - 1;
        }
    }

    PalindromeResult best{0, 1};
    for (int center = 0; center < n; ++center) {
        int oddLength = 2 * odd[center] - 1;
        if (oddLength > best.length)
            best = {center - odd[center] + 1, oddLength};
        int evenLength = 2 * even[center];
        if (evenLength > best.length)
            best = {center - even[center], evenLength};
    }
    return best;
}
