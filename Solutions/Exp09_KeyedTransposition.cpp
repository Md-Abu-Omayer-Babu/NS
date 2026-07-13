#include <bits/stdc++.h>
using namespace std;

string encrypt(string pt, string key) {
    int cols = key.length();
    int rows = (pt.length() + cols - 1) / cols;
    char mat[rows][cols];
    int idx = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            mat[i][j] = (idx < (int)pt.length()) ? pt[idx++] : 'X';
    pair<char, int> p[cols];
    for (int j = 0; j < cols; j++) p[j] = {key[j], j};
    sort(p, p + cols);
    string ct = "";
    for (int j = 0; j < cols; j++)
        for (int i = 0; i < rows; i++)
            ct += mat[i][p[j].second];
    return ct;
}

string decrypt(string ct, string key) {
    int cols = key.length();
    int rows = ct.length() / cols;
    char mat[rows][cols];
    pair<char, int> p[cols];
    for (int j = 0; j < cols; j++) p[j] = {key[j], j};
    sort(p, p + cols);
    int idx = 0;
    for (int j = 0; j < cols; j++)
        for (int i = 0; i < rows; i++)
            mat[i][p[j].second] = ct[idx++];
    string pt = "";
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            pt += mat[i][j];
    return pt;
}

int main() {
    string pt, key;
    cout << "Enter plaintext: ";
    getline(cin, pt);
    cout << "Enter key: ";
    getline(cin, key);
    string ct = encrypt(pt, key);
    cout << "Encrypted: " << ct << endl;
    cout << "Decrypted: " << decrypt(ct, key) << endl;
    return 0;
}
