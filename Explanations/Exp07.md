# Experiment 07: Implementation of Hill Cipher Using Matrix-Based Encryption and Decryption

## Problem Statement

Write a C++ program to implement the Hill Cipher. The program should take a plaintext message and a 2×2 key matrix, encrypt the message using matrix multiplication modulo 26, and then decrypt the ciphertext using the inverse of the key matrix.

## Introduction

The Hill Cipher is a polygraphic substitution cipher invented by Lester S. Hill in 1929. Unlike other ciphers that substitute individual letters, the Hill Cipher encrypts blocks of letters at a time using matrix multiplication. It was one of the first ciphers to use linear algebra in cryptography.

### Mathematical Formula

**Encryption:** `C = (K × P) mod 26`

**Decryption:** `P = (K⁻¹ × C) mod 26`

Where:
- **P** = Plaintext vector (2×1 matrix of letter positions)
- **C** = Ciphertext vector (2×1 matrix)
- **K** = 2×2 key matrix
- **K⁻¹** = Modular inverse of the key matrix modulo 26

### How to Find the Inverse of a 2×2 Matrix Modulo 26

For a 2×2 matrix `K = [[a, b], [c, d]]`:

1. Calculate determinant: `det = (a×d - b×c) mod 26`
2. Find modular inverse of determinant: `det⁻¹ mod 26`
3. The inverse matrix is: `det⁻¹ × [[d, -b], [-c, a]] mod 26`

The matrix is invertible only if GCD(det, 26) = 1.

### Example

Key Matrix: `[[3, 3], [2, 5]]`, Plaintext: `HELP`

P1 = H(7), E(4) → [7, 4]ᵀ
- C1 = (3×7 + 3×4) = 33 mod 26 = 7 → H
- C2 = (2×7 + 5×4) = 34 mod 26 = 8 → I

P2 = L(11), P(15) → [11, 15]ᵀ
- C1 = (3×11 + 3×15) = 78 mod 26 = 0 → A
- C2 = (2×11 + 5×15) = 97 mod 26 = 19 → T

Ciphertext: `HIAT`

## Solution Explanation

The program works as follows:

1. **Input:** The user enters a plaintext string and a 2×2 key matrix.

2. **Key Validation:** The program checks if the determinant is invertible modulo 26. If GCD(det, 26) ≠ 1, the key cannot be used for decryption.

3. **Plaintext Preparation:**
   - Remove non-letters and convert to uppercase.
   - If the length is odd, add 'X' to make it even (since we work with pairs).

4. **Encryption:**
   - Take plaintext letters in pairs.
   - Create a 2×1 vector from each pair.
   - Multiply by the key matrix: each ciphertext value = `(K[i][0] × P[0] + K[i][1] × P[1]) mod 26`.
   - Convert back to letters.

5. **Decryption:**
   - Compute the modular inverse of the determinant.
   - Construct the inverse matrix: swap a and d, negate b and c, multiply by det⁻¹.
   - Apply modulo to keep values in range 0-25.
   - Multiply the ciphertext vector by the inverse matrix.

### How the Code Works

- `modInverse(a, m)` — Finds the number `x` such that `(a × x) % m = 1`.
- `hillCipher(s, k, enc)` — The main function.
  - If encrypting, uses the key matrix directly.
  - If decrypting, computes the inverse matrix first.
  - Processes letters in pairs using the selected matrix.

### Running the Program

```
Enter plaintext: HELP
Enter 2x2 key matrix (4 numbers): 3 3 2 5
Encrypted: HIAT
Decrypted: HELP
```
