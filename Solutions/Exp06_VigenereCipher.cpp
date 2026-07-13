#include <bits/stdc++.h>
using namespace std;

string vigenere(string s, string key, bool enc) {
    string res = "";
    int kIdx = 0;
    for (char c : s) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            int shift = toupper(key[kIdx % key.length()]) - 'A';
            if (!enc) shift = 26 - shift;
            res += (c - base + shift) % 26 + base;
            kIdx++;
        } else res += c;
    }
    return res;
}

int main() {
    string pt, key;
    cout << "Enter plaintext: ";
    getline(cin, pt);
    cout << "Enter keyword: ";
    getline(cin, key);
    string ct = vigenere(pt, key, true);
    cout << "Encrypted: " << ct << endl;
    cout << "Decrypted: " << vigenere(ct, key, false) << endl;
    return 0;
}
