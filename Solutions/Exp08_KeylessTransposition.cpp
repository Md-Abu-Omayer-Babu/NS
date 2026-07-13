#include <bits/stdc++.h>
using namespace std;

string encrypt(string pt, int cols) {
    int rows = (pt.length() + cols - 1) / cols;
    char mat[rows][cols];
    int idx = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            mat[i][j] = (idx < (int)pt.length()) ? pt[idx++] : 'X';
    string ct = "";
    for (int j = 0; j < cols; j++)
        for (int i = 0; i < rows; i++)
            ct += mat[i][j];
    return ct;
}

string decrypt(string ct, int cols) {
    int rows = ct.length() / cols;
    char mat[rows][cols];
    int idx = 0;
    for (int j = 0; j < cols; j++)
        for (int i = 0; i < rows; i++)
            mat[i][j] = ct[idx++];
    string pt = "";
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            pt += mat[i][j];
    return pt;
}

int main() {
    string pt;
    int cols;
    cout << "Enter plaintext: ";
    getline(cin, pt);
    cout << "Enter number of columns: ";
    cin >> cols;
    string ct = encrypt(pt, cols);
    cout << "Encrypted: " << ct << endl;
    cout << "Decrypted: " << decrypt(ct, cols) << endl;
    return 0;
}
