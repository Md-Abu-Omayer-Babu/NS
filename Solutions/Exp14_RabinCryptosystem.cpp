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
    long long p, q;
    cout << "Enter prime p (≡ 3 mod 4): ";
    cin >> p;
    cout << "Enter prime q (≡ 3 mod 4): ";
    cin >> q;
    if (p % 4 != 3 || q % 4 != 3) {
        cout << "Both primes must be ≡ 3 mod 4." << endl;
        return 1;
    }
    long long n = p * q;
    long long m;
    cout << "Enter message (number < " << n << "): ";
    cin >> m;
    long long c = (m * m) % n;
    cout << "Encrypted: " << c << endl;
    long long mp = modPow(c, (p + 1) / 4, p);
    long long mq = modPow(c, (q + 1) / 4, q);
    long long invP = modInverse(p, q);
    long long invQ = modInverse(q, p);
    long long r1 = (mp * q * invQ + mq * p * invP) % n;
    long long r2 = (mp * q * invQ - mq * p * invP) % n;
    if (r1 < 0) r1 += n;
    if (r2 < 0) r2 += n;
    long long r3 = n - r1;
    long long r4 = n - r2;
    cout << "Possible plaintexts: " << r1 << ", " << r2 << ", " << r3 << ", " << r4 << endl;
    cout << "Original message: " << m << (m == r1 || m == r2 || m == r3 || m == r4 ? " [matched]" : " [not found]") << endl;
    return 0;
}
