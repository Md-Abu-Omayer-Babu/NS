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

string encrypt(string pt, int a, int b) {
    string ct = "";
    for (char c : pt) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            ct += ((c - base) * a + b) % 26 + base;
        } else ct += c;
    }
    return ct;
}

string decrypt(string ct, int a, int b) {
    int inv = modInverse(a, 26);
    if (inv == -1) return "[Error: 'a' not invertible mod 26]";
    string pt = "";
    for (char c : ct) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            pt += ((c - base - b + 26) * inv) % 26 + base;
        } else pt += c;
    }
    return pt;
}

int main() {
    string pt;
    int a, b;
    cout << "Enter plaintext: ";
    getline(cin, pt);
    cout << "Enter a (coprime with 26): ";
    cin >> a;
    cout << "Enter b: ";
    cin >> b;
    a = ((a % 26) + 26) % 26;
    b = ((b % 26) + 26) % 26;
    if (gcd(a, 26) != 1) {
        cout << "Invalid 'a': must be coprime with 26." << endl;
        return 1;
    }
    string ct = encrypt(pt, a, b);
    cout << "Encrypted: " << ct << endl;
    cout << "Decrypted: " << decrypt(ct, a, b) << endl;
    return 0;
}
