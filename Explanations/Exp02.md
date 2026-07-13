# Experiment 02: Implementation of Multiplicative Cipher for Encryption and Decryption

## Problem Statement

Write a C++ program to perform encryption and decryption using the Multiplicative Cipher. The program should take a plaintext message and a key value, encrypt the message by multiplying each letter's position by the key, and then decrypt the ciphertext back.

## Introduction

The Multiplicative Cipher is a type of substitution cipher where each letter is replaced by another letter using multiplication instead of addition. It works by multiplying the numeric position of each plaintext letter by a key value, then taking the result modulo 26.

### Mathematical Formula

Encryption: `C = (P * K) mod 26`

Decryption: `P = (C * K⁻¹) mod 26`

Where:
- **P** = Plaintext letter position (0-25)
- **C** = Ciphertext letter position
- **K** = Key (must be coprime with 26)
- **K⁻¹** = Modular multiplicative inverse of K modulo 26

### Key Concepts

- **Coprime (Relatively Prime):** Two numbers are coprime if their GCD (Greatest Common Divisor) is 1. The key must be coprime with 26 for the cipher to work. If GCD(K, 26) > 1, then multiple plaintext letters map to the same ciphertext letter, making decryption impossible.
- **Modular Inverse:** The modular inverse K⁻¹ is a number such that `(K * K⁻¹) mod 26 = 1`. It is used for decryption.
- **Valid keys:** Only 1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25 (12 keys total).

### Example

Plaintext: `HELLO`, Key = 5
- H(7) * 5 = 35 mod 26 = 9 → J
- E(4) * 5 = 20 mod 26 = 20 → U
- L(11) * 5 = 55 mod 26 = 3 → D
- L(11) * 5 = 55 mod 26 = 3 → D
- O(14) * 5 = 70 mod 26 = 18 → S

Ciphertext: `JUDDS`

## Solution Explanation

The program works in the following steps:

1. **Input:** The user enters a plaintext string and a key number.

2. **Key Validation:** The program checks if the key is coprime with 26 using the GCD function. If `GCD(key, 26) != 1`, it shows an error and stops. This is important because an invalid key would make decryption impossible.

3. **Encryption:**
   - For each letter in the plaintext, convert to its numeric position (0-25).
   - Multiply by the key, take `mod 26`, and convert back to a letter.
   - Non-letter characters are kept unchanged.

4. **Finding the Modular Inverse:**
   - The program searches for a number `inv` between 1 and 25 such that `(key * inv) % 26 == 1`.
   - This `inv` is the decryption key.

5. **Decryption:**
   - For each letter in the ciphertext, multiply its position by the inverse key, take `mod 26`, and convert back to a letter.

### How the Code Works

- `modInverse(a, m)` — Finds the modular inverse of `a` modulo `m` by trying numbers from 1 to m-1.
- `gcd(a, b)` — Calculates the GCD using the Euclidean algorithm (repeated division).
- `encrypt(pt, k)` — Multiplies each letter position by `k` and applies mod 26.
- `decrypt(ct, k)` — First gets the modular inverse of `k`, then multiplies each ciphertext letter position by it.

### Running the Program

```
Enter plaintext: Hello
Enter key (coprime with 26): 5
Encrypted: Judds
Decrypted: Hello
```
