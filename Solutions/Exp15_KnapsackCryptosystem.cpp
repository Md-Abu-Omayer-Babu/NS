#include <bits/stdc++.h>
using namespace std;

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
    int n;
    cout << "Enter knapsack size: ";
    cin >> n;
    vector<long long> w(n);
    cout << "Enter " << n << " superincreasing values: ";
    for (int i = 0; i < n; i++) cin >> w[i];
    long long sum = 0;
    for (long long v : w) {
        if (v <= sum) {
            cout << "Sequence is not superincreasing!" << endl;
            return 1;
        }
        sum += v;
    }
    long long m, a;
    cout << "Enter modulus m (> " << sum << "): ";
    cin >> m;
    cout << "Enter multiplier a (coprime with " << m << "): ";
    cin >> a;
    if (gcd(a, m) != 1) {
        cout << "a must be coprime with m." << endl;
        return 1;
    }
    vector<long long> b(n);
    for (int i = 0; i < n; i++) b[i] = (a * w[i]) % m;
    cout << "Public key: ";
    for (long long v : b) cout << v << " ";
    cout << endl;
    cin.ignore();
    string msg;
    cout << "Enter binary message (" << n << " bits): ";
    getline(cin, msg);
    long long ct = 0;
    for (int i = 0; i < n && i < (int)msg.length(); i++)
        if (msg[i] == '1') ct += b[i];
    cout << "Encrypted: " << ct << endl;
    long long invA = modInverse(a, m);
    long long s = (ct * invA) % m;
    string pt = "";
    for (int i = n - 1; i >= 0; i--) {
        if (s >= w[i]) {
            pt = "1" + pt;
            s -= w[i];
        } else pt = "0" + pt;
    }
    cout << "Decrypted: " << pt << endl;
    return 0;
}
