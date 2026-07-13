# Experiment 01: Implementation of Additive Cipher for Encryption and Decryption

## Problem Statement

Write a C++ program to perform encryption and decryption using the Additive Cipher (also known as Caesar Cipher). The program should take a plaintext message and a key (shift value) as input from the user, encrypt the message, and then decrypt the ciphertext back to the original plaintext.

## Introduction

The Additive Cipher is one of the oldest and simplest encryption techniques. It is a type of substitution cipher where each letter in the plaintext is replaced by a letter some fixed number of positions down the alphabet.

**Also known as:** Caesar Cipher (named after Julius Caesar, who used it with a shift of 3).

### Mathematical Formula

Encryption: `C = (P + K) mod 26`

Decryption: `P = (C - K) mod 26`

Where:
- **P** = Plaintext letter's position (A=0, B=1, ..., Z=25)
- **C** = Ciphertext letter's position
- **K** = Key (shift value between 0 and 25)

### Key Concepts

- **Substitution cipher:** Each letter is replaced by another letter.
- **Modular arithmetic:** We use `mod 26` because there are 26 letters in the English alphabet. When the shift goes past Z, it wraps around to A.
- **Symmetric cipher:** The same key is used for both encryption and decryption.
- **Key space:** Only 26 possible keys (0 to 25), making it very easy to break by brute force.

### Example

Plaintext: `HELLO`, Key = 3
- H(7) + 3 = 10 → K
- E(4) + 3 = 7 → H
- L(11) + 3 = 14 → O
- L(11) + 3 = 14 → O
- O(14) + 3 = 17 → R

Ciphertext: `KHOOR`

## Solution Explanation

The program works in three simple steps:

1. **Input:** The user enters a plaintext string and a key number between 0 and 25.

2. **Encryption:**
   - The program goes through each character of the plaintext one by one.
   - If the character is a letter (A-Z or a-z), it finds the letter's position (0 to 25) by subtracting the base ('A' for uppercase, 'a' for lowercase).
   - It adds the key to this position and takes `mod 26` to wrap around if needed.
   - It converts the new position back to a letter and adds it to the ciphertext.
   - Non-letter characters (spaces, numbers, punctuation) are kept as they are.

3. **Decryption:**
   - To decrypt, we use the same encrypt function but with a twist: instead of passing the original key `K`, we pass `26 - K`. This effectively shifts backwards.
   - This works because `(C - K) mod 26 = (C + (26 - K)) mod 26`.

### How the Code Works

The code defines two functions:
- `encrypt(pt, k)` — Shifts each letter forward by `k` positions.
- `decrypt(ct, k)` — Calls `encrypt(ct, 26 - k)` to shift backward.

The `main()` function takes user input, calls `encrypt()` to get the ciphertext, prints it, then calls `decrypt()` on the ciphertext to verify it returns the original plaintext.

### Running the Program

```
Enter plaintext: Hello World
Enter key (0-25): 3
Encrypted: Khoor Zruog
Decrypted: Hello World
```
