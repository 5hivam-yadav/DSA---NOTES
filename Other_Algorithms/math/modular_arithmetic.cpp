#include <bits/stdc++.h>
using namespace std;

long long modPow(long long base, long long exponent, long long mod) {
    if (mod <= 0 || exponent < 0)
        throw invalid_argument(
            "mod must be positive and exponent non-negative");
    base %= mod;
    if (base < 0)
        base += mod;
    long long result = 1 % mod;
    while (exponent > 0) {
        if (exponent & 1)
            result = (long long)((__int128)result * base % mod);
        base = (long long)((__int128)base * base % mod);
        exponent >>= 1;
    }
    return result;
}

long long extendedGcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = (a >= 0) ? 1 : -1;
        y = 0;
        return llabs(a);
    }
    long long nextX, nextY;
    long long gcd = extendedGcd(b, a % b, nextX, nextY);
    x = nextY;
    y = nextX - (a / b) * nextY;
    return gcd;
}

optional<long long> modularInverse(long long value, long long mod) {
    long long x, y;
    if (mod <= 1 || extendedGcd(value, mod, x, y) != 1)
        return nullopt;
    x %= mod;
    if (x < 0)
        x += mod;
    return x;
}
