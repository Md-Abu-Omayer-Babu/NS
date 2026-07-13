#include <bits/stdc++.h>
using namespace std;

string prepare(string s) {
    string res = "";
    for (char c : s) {
        if (isalpha(c)) {
            c = toupper(c);
            if (c == 'J') c = 'I';
            res += c;
        }
    }
    for (size_t i = 0; i < res.length(); i += 2) {
        if (i + 1 == res.length())
            res += 'X';
        else if (res[i] == res[i + 1])
            res.insert(i + 1, "X");
    }
    return res;
}

void findPos(char c, char mat[5][5], int &r, int &col) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (mat[i][j] == c) {
                r = i;
                col = j;
                return;
            }
}

string playfair(string s, char mat[5][5], bool enc) {
    string res = "";
    int dir = enc ? 1 : -1;
    for (size_t i = 0; i < s.length(); i += 2) {
        int r1, c1, r2, c2;
        findPos(s[i], mat, r1, c1);
        findPos(s[i + 1], mat, r2, c2);
        if (r1 == r2) {
            res += mat[r1][(c1 + dir + 5) % 5];
            res += mat[r2][(c2 + dir + 5) % 5];
        } else if (c1 == c2) {
            res += mat[(r1 + dir + 5) % 5][c1];
            res += mat[(r2 + dir + 5) % 5][c2];
        } else {
            res += mat[r1][c2];
            res += mat[r2][c1];
        }
    }
    return res;
}

int main() {
    string key, pt;
    cout << "Enter key: ";
    getline(cin, key);
    cout << "Enter plaintext: ";
    getline(cin, pt);
    string k = "";
    bool seen[26] = {false};
    for (char c : key) {
        if (isalpha(c)) {
            c = toupper(c);
            if (c == 'J') c = 'I';
            if (!seen[c - 'A']) {
                seen[c - 'A'] = true;
                k += c;
            }
        }
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue;
        if (!seen[c - 'A']) k += c;
    }
    char mat[5][5];
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            mat[i][j] = k[i * 5 + j];
    string prep = prepare(pt);
    string ct = playfair(prep, mat, true);
    cout << "Encrypted: " << ct << endl;
    cout << "Decrypted: " << playfair(ct, mat, false) << endl;
    return 0;
}
