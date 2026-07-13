# Experiment 10: Implementation of Hybrid Transposition Cipher Technique for Secure Message Encryption and Decryption

## Problem Statement

Write a C++ program to implement a Hybrid Transposition Cipher that combines both Keyless Transposition and Keyed Transposition techniques. The program should apply both operations sequentially to encrypt a message and then reverse the operations in the correct order for decryption.

## Introduction

A Hybrid Transposition Cipher combines two or more transposition techniques to create a more secure encryption. This implementation first applies a Keyless Transposition (write row-wise, read column-wise) and then applies a Keyed Transposition (write row-wise, read in keyword-determined column order). By combining both, the resulting scrambling is much more thorough than either technique alone.

### How the Combination Works

**Encryption Process:**
1. **Step 1 (Keyless):** Write plaintext into grid row-wise, read column-wise using a fixed number of columns.
2. **Step 2 (Keyed):** Take the result from Step 1, write it into a new grid row-wise, read columns in the order determined by sorting a keyword.

**Decryption Process:** (reverse order)
1. **Step 1 (Keyed Decrypt):** Write ciphertext into grid in keyword column order, read row-wise.
2. **Step 2 (Keyless Decrypt):** Write result into grid column-wise, read row-wise.

### Security Benefit

- The keyless step scrambles the positions at a basic level.
- The keyed step adds a second layer of scrambling controlled by a keyword.
- An attacker must know both the number of columns AND the keyword to recover the message.

### Example

Plaintext: `HELLO WORLD`, Columns: 4, Keyword: `KEY`

**Step 1 (Keyless):** `HORELLWDLOX` (from Exp08)
**Step 2 (Keyed with KEY):** Apply keyed transposition on "HORELLWDLOX"

Length: 11, Keyword length: 3, rows = 4

Grid (keyed):
```
H O R
E L L
W D L
O X X
```

Keyword: K(10), E(4), Y(24) → sorted order: E(1), K(0), Y(2)

Column 1: O, L, D, X
Column 0: H, E, W, O
Column 2: R, L, L, X

Ciphertext: `OLDXHEWORLLX` → `OLDXHEWORLLX`

## Solution Explanation

The program works in two stages:

1. **Input:** User enters plaintext, number of columns (for keyless step), and keyword (for keyed step).

2. **Encryption:**
   - Apply keyless transposition: fill grid row-wise using columns, read column-wise.
   - Apply keyed transposition: fill grid row-wise using keyword length, read in keyword-sorted column order.

3. **Decryption:**
   - Apply keyed decryption: fill grid in keyword-sorted column order, read row-wise.
   - Apply keyless decryption: fill grid column-wise using columns, read row-wise.

### How the Code Works

The program reuses the same functions from Exp08 and Exp09:
- `keylessEncrypt(pt, cols)` and `keylessDecrypt(ct, cols)`
- `keyedEncrypt(pt, key)` and `keyedDecrypt(ct, key)`

The `main()` function chains them:
- Encryption: `ct = keyedEncrypt(keylessEncrypt(pt, cols), key)`
- Decryption: `pt = keylessDecrypt(keyedDecrypt(ct, key), cols)`

### Running the Program

```
Enter plaintext: HELLO WORLD
Enter number of columns: 4
Enter key: KEY
Encrypted: OLDXHEWORLLX
Decrypted: HELLO WORLDXX
```
