#include <bits/stdc++.h>
using namespace std;

int modInverse(int a, int m) {
    a = (a % m + m) % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1) return x;
    return -1;
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

string encrypt(string pt, int k) {
    string ct = "";
    for (char c : pt) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            ct += ((c - base) * k) % 26 + base;
        } else ct += c;
    }
    return ct;
}

string decrypt(string ct, int k) {
    int inv = modInverse(k, 26);
    if (inv == -1) return "[Error: key not invertible mod 26]";
    string pt = "";
    for (char c : ct) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            pt += ((c - base) * inv) % 26 + base;
        } else pt += c;
    }
    return pt;
}

int main() {
    string pt;
    int k;
    cout << "Enter plaintext: ";
    getline(cin, pt);
    cout << "Enter key (coprime with 26): ";
    cin >> k;
    k = ((k % 26) + 26) % 26;
    if (gcd(k, 26) != 1) {
        cout << "Invalid key: must be coprime with 26." << endl;
        return 1;
    }
    string ct = encrypt(pt, k);
    cout << "Encrypted: " << ct << endl;
    cout << "Decrypted: " << decrypt(ct, k) << endl;
    return 0;
}
