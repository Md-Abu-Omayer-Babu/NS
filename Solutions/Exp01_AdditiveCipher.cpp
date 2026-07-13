#include <bits/stdc++.h>
using namespace std;

string encrypt(string pt, int k) {
    string ct = "";
    for (char c : pt) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            ct += (c - base + k) % 26 + base;
        } else ct += c;
    }
    return ct;
}

string decrypt(string ct, int k) {
    return encrypt(ct, 26 - (k % 26));
}

int main() {
    string pt;
    int k;
    cout << "Enter plaintext: ";
    getline(cin, pt);
    cout << "Enter key (0-25): ";
    cin >> k;
    k = ((k % 26) + 26) % 26;
    string ct = encrypt(pt, k);
    cout << "Encrypted: " << ct << endl;
    cout << "Decrypted: " << decrypt(ct, k) << endl;
    return 0;
}
