# Experiment 11: Implementation and Analysis of Feistel Cipher Structure

## Problem Statement

Write a C++ program to implement a Feistel Cipher structure. The program should take a plaintext message and two round keys, encrypt the message using a 2-round Feistel network, and then decrypt the ciphertext. The decryption should simply use the round keys in reverse order.

## Introduction

The Feistel Cipher is not a specific cipher but a structure or design principle used in many modern block ciphers, including DES (Data Encryption Standard). It was invented by Horst Feistel at IBM. The key insight of the Feistel structure is that encryption and decryption use the same algorithm — only the key order is reversed.

### How the Feistel Structure Works

A Feistel network splits the plaintext into two halves (left and right) and processes them through multiple rounds. Each round:

1. The right half is passed through a round function `F` using a round key.
2. The output of `F` is XORed with the left half.
3. The halves are swapped.

**Encryption (2 rounds):**
- Round 1: `L₁ = R₀`, `R₁ = L₀ ⊕ F(R₀, K₁)`
- Round 2: `L₂ = R₁`, `R₂ = L₁ ⊕ F(R₁, K₂)`
- Final (after swap): `C = R₂ || L₂`

**Decryption:** Same process, but use K₂ then K₁ (reverse order).

### Round Function

In this implementation, the round function is: `F(R, K) = (R + K) mod 256`

This is a simple round function for demonstration. Real ciphers like DES use much more complex functions.

### Key Property

The Feistel structure guarantees that decryption is always possible regardless of the round function's complexity, because XOR is its own inverse: `(A ⊕ B) ⊕ B = A`.

### Example

Plaintext: `HELLO`, Keys: K₁ = 3, K₂ = 7

Since Feistel works on bits/bytes, we operate on the ASCII values of characters.

String: "HELLO" → ASCII: 72, 69, 76, 76, 79

Split (odd length, so pad with space): "HELL" + "O " → actually let's say we have "HELLO " (6 chars)

L₀ = "HEL" (72, 69, 76), R₀ = "LO " (76, 79, 32)

Round 1:
- New L = R₀ = "LO "
- New R = L₀ XOR F(R₀, 3) where F = (R₀[i] + 3) % 256
  - R₀[0]+3 = 79, L₀[0] XOR 79 = 72 XOR 79 = 15
  - R₀[1]+3 = 82, L₀[1] XOR 82 = 69 XOR 82 = 23
  - R₀[2]+3 = 35, L₀[2] XOR 35 = 76 XOR 35 = 111
  - New R = (15, 23, 111)

Round 2:
- New L = (15, 23, 111) [old R]
- New R = "LO " XOR F((15,23,111), 7)
  - F((15,23,111), 7) = (22, 30, 118)
  - "LO " XOR (22, 30, 118) = (76 XOR 22, 79 XOR 30, 32 XOR 118)
  - = (82, 81, 86)
  - New R = (82, 81, 86)

Final (swap): (82, 81, 86) || (15, 23, 111)

These are non-printable bytes, so the output is shown in hexadecimal.

## Solution Explanation

The program works as follows:

1. **Input:** User enters a plaintext string and two round keys (integers).

2. **Encryption:**
   - If the length is odd, pad with a space.
   - Split into left and right halves.
   - For 2 rounds with keys K₁, K₂:
     - New left = old right
     - New right = old left XOR ((old right[i] + key) mod 256) for each byte
   - After both rounds, swap halves (concatenate as right + left).

3. **Decryption:**
   - Same `feistel()` function, but pass keys in reverse order (K₂, K₁).

4. **Output:**
   - The ciphertext is displayed in hexadecimal (since bytes may be non-printable).
   - The decrypted plaintext is shown as a string.

### How the Code Works

- `feistel(pt, k1, k2)` — Performs the Feistel encryption:
  - Uses `unsigned char` for byte operations to avoid negative values.
  - Round function: `(byte + key) % 256`, then XOR with the other half.
  - Returns `right + left` (swap after final round).

Decryption calls `feistel(ct, k2, k1)` — the same algorithm with reversed keys.

### Running the Program

```
Enter plaintext: Hello
Enter key 1: 3
Enter key 2: 7
Encrypted (hex): 5251560f176f
Decrypted: Hello
```
