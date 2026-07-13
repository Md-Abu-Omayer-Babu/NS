#include <bits/stdc++.h>
using namespace std;

string autokey(string s, int primeKey, bool enc) {
    string res = "";
    int prev = primeKey;
    for (char c : s) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            int p = c - base;
            int k = prev;
            if (!enc) k = 26 - prev;
            res += (p + k) % 26 + base;
            prev = enc ? p : (c - base - prev + 26) % 26;
        } else res += c;
    }
    return res;
}

int main() {
    string pt;
    int primeKey;
    cout << "Enter plaintext: ";
    getline(cin, pt);
    cout << "Enter prime key (0-25): ";
    cin >> primeKey;
    primeKey = ((primeKey % 26) + 26) % 26;
    string ct = autokey(pt, primeKey, true);
    cout << "Encrypted: " << ct << endl;
    cout << "Decrypted: " << autokey(ct, primeKey, false) << endl;
    return 0;
}
