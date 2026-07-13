# Experiment 05: Implementation of Playfair Cipher for Secure Text Encryption and Decryption

## Problem Statement

Write a C++ program to implement the Playfair Cipher. The program should take a keyword and a plaintext message, construct a 5×5 key matrix, encrypt the message in digraphs (pairs of letters), and then decrypt the ciphertext back to the original plaintext.

## Introduction

The Playfair Cipher is a digraph substitution cipher invented by Charles Wheatstone in 1854 and promoted by Lord Playfair. It encrypts pairs of letters (digraphs) instead of single letters, making it harder to break than simple substitution ciphers. It was used by the British military in World War I.

### How the 5×5 Matrix is Built

1. Remove duplicate letters from the keyword.
2. Fill the matrix row by row with the remaining keyword letters.
3. Fill the rest of the matrix with the remaining letters of the alphabet (A to Z).
4. Treat I and J as the same letter (to fit 26 letters into 25 cells).

### Encryption Rules

For each pair of letters (digraph):

1. **Same row:** Replace each letter with the letter to its right (wrap around).
2. **Same column:** Replace each letter with the letter below it (wrap around).
3. **Rectangle:** Replace each letter with the letter in the same row but the other letter's column (form a rectangle).

### Preparation Rules

- Remove non-letters and convert to uppercase.
- Replace J with I.
- If a pair has two identical letters, insert X between them.
- If the plaintext has an odd length, add X at the end.

### Example

Keyword: `MONARCHY`, Plaintext: `HELLO`

Matrix:
```
M O N A R
C H Y B D
E F G I/J K
L P Q S T
U V W X Z
```

After preparation: `HE LX LO`

- HE: Same column (col 1) → C(2,1) + Y(1,2)... wait let me be more precise.

Actually let me use the matrix:
```
M O N A R
C H Y B D
E F G I K
L P Q S T
U V W X Z
```

- H(2,2), E(3,1) → Rectangle: H row 2 col 1 = C, E row 3 col 2 = F → CF
- L(4,1), X(5,4) → Rectangle: L row 4 col 4 = S, X row 5 col 1 = U → SU
- L(4,1), O(1,2) → Rectangle: L row 4 col 2 = P, O row 1 col 1 = M → PM

Ciphertext: `CFSUPM`

## Solution Explanation

The program works in several stages:

**Stage 1: Build the Key Matrix**
- Remove duplicate letters from the keyword.
- Fill the matrix with keyword letters, then remaining alphabet letters.
- I and J share the same cell.

**Stage 2: Prepare the Plaintext**
- Convert to uppercase, remove non-letters, replace J with I.
- Insert X between identical letter pairs.
- Add X if the length is odd.

**Stage 3: Encrypt Digraphs**
- For each pair of letters, find their positions in the matrix.
- Apply the appropriate rule (same row, same column, or rectangle).
- For decryption, shift left (row) or up (column) instead of right/down.

**Stage 4: Decryption**
- Same as encryption, but with direction reversed.
- Rectangle rule works the same both ways.

### How the Code Works

- `prepare(s)` — Cleans and prepares the plaintext for encryption.
- `findPos(c, mat, r, col)` — Finds the row and column of a letter in the matrix.
- `playfair(s, mat, enc)` — Encrypts or decrypts a prepared string using the matrix.
  - Uses `dir = 1` for encryption (right/down) and `dir = -1` for decryption (left/up).
  - For same row: shift columns by dir.
  - For same column: shift rows by dir.
  - For rectangle: swap columns.

### Running the Program

```
Enter key: MONARCHY
Enter plaintext: HELLO
Encrypted: CFSUPM
Decrypted: HELXLO
```

Note: The decrypted output may differ slightly from the original due to inserted X's (padding), but the original message content is preserved.
