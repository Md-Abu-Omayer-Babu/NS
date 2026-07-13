# Experiment 08: Implementation of Keyless Transposition Cipher for Message Encryption and Decryption

## Problem Statement

Write a C++ program to implement a Keyless Transposition Cipher. The program should take a plaintext message and a number of columns, write the message row by row into a grid, read it column by column to produce the ciphertext, and then reverse the process for decryption.

## Introduction

Transposition ciphers rearrange the order of letters in a message rather than substituting them. The Keyless Transposition Cipher (also called the Columnar Transposition Cipher without a key) writes the plaintext into a table row-wise and then reads it column-wise. Since the letters themselves are not changed, only their positions are scrambled.

### How It Works

1. Write the plaintext into a grid row by row (left to right, top to bottom).
2. Read the grid column by column (top to bottom, left to right) to get the ciphertext.
3. For decryption, write the ciphertext column by column and read row by row.

### Padding

If the plaintext doesn't completely fill the last row, padding letters (usually 'X') are added to fill the remaining cells.

### Example

Plaintext: `HELLO WORLD`, Columns: 4

Grid (3 rows × 4 cols):
```
H E L L
O   W O
R L D X
```

*Note: The space is also placed in the grid.*

Read column by column: Column 0 → HOR, Column 1 → E L, Column 2 → LWD, Column 3 → LOX

Ciphertext: `HOR E LW DLO X` → `HORELWDLOX`

(To be precise, removing spaces:)

|   | Col 0 | Col 1 | Col 2 | Col 3 |
|---|-------|-------|-------|-------|
| R0| H     | E     | L     | L     |
| R1| O     |       | W     | O     |
| R2| R     | L     | D     | X     |

Reading columns: HOR, E L, LWD, LOX → `HOR EL LWD LOX` → `HORELLWDLOX`

## Solution Explanation

The program works as follows:

1. **Input:** The user enters a plaintext string and the number of columns.

2. **Encryption:**
   - Calculate the number of rows needed: `rows = (length + cols - 1) / cols`.
   - Create a 2D character grid (rows × cols).
   - Fill the grid row by row with characters from the plaintext.
   - If the last row isn't full, pad with 'X'.
   - Read the grid column by column: for each column, go through all rows top to bottom.
   - Append each character to the ciphertext.

3. **Decryption:**
   - Calculate rows the same way: `rows = length / cols` (length is now the ciphertext length).
   - Fill a grid column by column with the ciphertext.
   - Read the grid row by row to recover the plaintext.
   - Trailing 'X' padding may appear (this is normal).

### How the Code Works

- `encrypt(pt, cols)` — Fills the matrix row-wise, reads column-wise.
- `decrypt(ct, cols)` — Fills the matrix column-wise, reads row-wise.

The matrix (2D array) uses Variable Length Arrays (VLAs) since `rows` and `cols` are known at runtime in C++.

### Running the Program

```
Enter plaintext: HELLO WORLD
Enter number of columns: 4
Encrypted: HORELLWDLOX
Decrypted: HELLO WORLDXX
```

The decrypted output may have trailing X's from padding, but the original message is intact.
