#include <bits/stdc++.h>
using namespace std;

int modInverse(int a, int m) {
    a = (a % m + m) % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1) return x;
    return -1;
}

string hillCipher(string s, int k[2][2], bool enc) {
    string clean = "";
    for (char c : s)
        if (isalpha(c)) clean += toupper(c);
    if (clean.length() % 2) clean += 'X';
    int det = (k[0][0] * k[1][1] - k[0][1] * k[1][0]) % 26;
    if (det < 0) det += 26;
    int invDet = modInverse(det, 26);
    if (!enc && invDet == -1) return "[Error: matrix not invertible]";
    int mk[2][2];
    if (enc) {
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                mk[i][j] = k[i][j];
    } else {
        mk[0][0] = (k[1][1] * invDet) % 26;
        mk[0][1] = (-k[0][1] * invDet) % 26;
        mk[1][0] = (-k[1][0] * invDet) % 26;
        mk[1][1] = (k[0][0] * invDet) % 26;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                mk[i][j] = (mk[i][j] + 26) % 26;
    }
    string res = "";
    for (size_t i = 0; i < clean.length(); i += 2) {
        int a = clean[i] - 'A', b = clean[i + 1] - 'A';
        int c1 = (mk[0][0] * a + mk[0][1] * b) % 26;
        int c2 = (mk[1][0] * a + mk[1][1] * b) % 26;
        res += (c1 + 'A');
        res += (c2 + 'A');
    }
    return res;
}

int main() {
    string pt;
    int k[2][2];
    cout << "Enter plaintext: ";
    getline(cin, pt);
    cout << "Enter 2x2 key matrix (4 numbers): ";
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            cin >> k[i][j];
    int det = (k[0][0] * k[1][1] - k[0][1] * k[1][0]) % 26;
    if (det < 0) det += 26;
    if (modInverse(det, 26) == -1) {
        cout << "Matrix not invertible mod 26." << endl;
        return 1;
    }
    string ct = hillCipher(pt, k, true);
    cout << "Encrypted: " << ct << endl;
    cout << "Decrypted: " << hillCipher(ct, k, false) << endl;
    return 0;
}
