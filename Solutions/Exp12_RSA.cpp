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

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    long long p, q;
    cout << "Enter prime p: ";
    cin >> p;
    cout << "Enter prime q: ";
    cin >> q;
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    long long e = 2;
    for (; e < phi; e++)
        if (gcd(e, phi) == 1) break;
    long long d = modInverse(e, phi);
    cout << "Public key (e, n): (" << e << ", " << n << ")" << endl;
    cout << "Private key (d, n): (" << d << ", " << n << ")" << endl;
    long long m;
    cout << "Enter message (as number < " << n << "): ";
    cin >> m;
    long long c = modPow(m, e, n);
    cout << "Encrypted: " << c << endl;
    cout << "Decrypted: " << modPow(c, d, n) << endl;
    return 0;
}
