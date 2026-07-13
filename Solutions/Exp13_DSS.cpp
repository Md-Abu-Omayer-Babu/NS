#include <bits/stdc++.h>
using namespace std;

long long modPow(long long b, long long e, long long m) {
    long long r = 1;
    b %= m;
    while (e > 0) {
        if (e & 1) r = (r * b) % m;
        b = (b * b) % m;
        e >>= 1;
    }
    return r;
}

long long modInverse(long long a, long long m) {
    a = (a % m + m) % m;
    for (long long x = 1; x < m; x++)
        if ((a * x) % m == 1) return x;
    return -1;
}

int main() {
    srand(time(0));
    long long q = 11, p = 23;
    long long h = 2;
    long long g = modPow(h, (p - 1) / q, p);
    long long x = (rand() % (q - 1)) + 1;
    long long y = modPow(g, x, p);
    cout << "Domain params (p, q, g): (" << p << ", " << q << ", " << g << ")" << endl;
    cout << "Public key y: " << y << endl;
    cout << "Private key x: " << x << endl;
    long long Hm;
    cout << "Enter message hash (number): ";
    cin >> Hm;
    long long k = (rand() % (q - 1)) + 1;
    long long r = modPow(g, k, p) % q;
    long long invK = modInverse(k, q);
    long long s = (invK * ((Hm % q) + x * r)) % q;
    if (s < 0) s += q;
    cout << "Signature (r, s): (" << r << ", " << s << ")" << endl;
    long long w = modInverse(s, q);
    long long u1 = ((Hm % q) * w) % q;
    long long u2 = (r * w) % q;
    long long v = (modPow(g, u1, p) * modPow(y, u2, p)) % p % q;
    cout << "Verification v: " << v << (v == r ? " [Valid]" : " [Invalid]") << endl;
    return 0;
}
