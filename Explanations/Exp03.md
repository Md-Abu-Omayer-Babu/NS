# Experiment 03: Implementation of Affine Cipher Technique for Secure Message Encryption and Decryption

## Problem Statement

Write a C++ program to implement the Affine Cipher, which combines both additive and multiplicative techniques. The program should take a plaintext message and two keys (a and b), encrypt the message, and then decrypt it back to the original.

## Introduction

The Affine Cipher is a combination of the Multiplicative Cipher and the Additive Cipher. It uses two keys: one multiplier (a) and one shift (b). This gives it a larger key space and makes it more secure than either cipher alone.

### Mathematical Formula

Encryption: `C = (a * P + b) mod 26`

Decryption: `P = a⁻¹ * (C - b) mod 26`

Where:
- **P** = Plaintext letter position (0-25)
- **C** = Ciphertext letter position
- **a** = Multiplicative key (must be coprime with 26)
- **b** = Additive key (any number 0-25)
- **a⁻¹** = Modular inverse of a modulo 26

### Key Concepts

- **Two-part key:** The key consists of `(a, b)`. This gives `12 * 26 = 312` possible keys.
- **Invertibility requirement:** The multiplier `a` must be coprime with 26, just like in the Multiplicative Cipher. If GCD(a, 26) ≠ 1, decryption is impossible.
- **Combination:** The cipher first multiplies, then adds. This makes it an affine transformation (linear function plus constant).

### Example

Plaintext: `HELLO`, Keys: a = 5, b = 8
- H(7): (5*7 + 8) = 43 mod 26 = 17 → R
- E(4): (5*4 + 8) = 28 mod 26 = 2 → C
- L(11): (5*11 + 8) = 63 mod 26 = 11 → L
- L(11): (5*11 + 8) = 63 mod 26 = 11 → L
- O(14): (5*14 + 8) = 78 mod 26 = 0 → A

Ciphertext: `RCLLA`

## Solution Explanation

The program follows these steps:

1. **Input:** The user enters a plaintext string and two keys `a` and `b`.

2. **Key Validation:** The program checks that `a` is coprime with 26. If not, it shows an error.

3. **Encryption:**
   - For each letter, get its numeric position P.
   - Compute `(a * P + b) mod 26`.
   - Convert back to a letter and add to ciphertext.

4. **Finding Modular Inverse:**
   - Find `a⁻¹` such that `(a * a⁻¹) mod 26 = 1`.
   - This inverse is needed for decryption.

5. **Decryption:**
   - For each ciphertext letter, get its position C.
   - Compute `a⁻¹ * (C - b + 26) mod 26`.
   - The `+26` ensures the value doesn't go negative before the mod operation.
   - Convert back to a letter.

### How the Code Works

- `modInverse(a, m)` — Finds the value `inv` such that `(a * inv) % m == 1`.
- `encrypt(pt, a, b)` — Multiplies by `a`, adds `b`, takes `mod 26`.
- `decrypt(ct, a, b)` — Computes `(C - b + 26)`, multiplies by `a⁻¹`, takes `mod 26`.

The `+ 26` in the decryption formula `(c - base - b + 26) * inv % 26` ensures the subtraction doesn't produce a negative number before the modulo operation.

### Running the Program

```
Enter plaintext: Hello
Enter a (coprime with 26): 5
Enter b: 8
Encrypted: Rclla
Decrypted: Hello
```
