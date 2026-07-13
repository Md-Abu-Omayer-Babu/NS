#include <bits/stdc++.h>
using namespace std;

string feistel(string pt, int k1, int k2) {
    int n = pt.length();
    if (n % 2) pt += ' ';
    n = pt.length();
    string L = pt.substr(0, n / 2);
    string R = pt.substr(n / 2);
    int keys[2] = {k1, k2};
    for (int r = 0; r < 2; r++) {
        string newL = R;
        string newR = "";
        for (int i = 0; i < (int)R.length(); i++) {
            unsigned char f = (unsigned char)(R[i] + keys[r]);
            newR += (unsigned char)((unsigned char)L[i] ^ f);
        }
        L = newL;
        R = newR;
    }
    return R + L;
}

int main() {
    string pt;
    int k1, k2;
    cout << "Enter plaintext: ";
    getline(cin, pt);
    cout << "Enter key 1: ";
    cin >> k1;
    cout << "Enter key 2: ";
    cin >> k2;
    string ct = feistel(pt, k1, k2);
    cout << "Encrypted (hex): ";
    for (size_t i = 0; i < ct.length(); i++)
        printf("%02x", (unsigned char)ct[i]);
    cout << endl;
    string dt = feistel(ct, k2, k1);
    cout << "Decrypted: " << dt << endl;
    return 0;
}
