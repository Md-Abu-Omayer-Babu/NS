# Experiment 06: Implementation of Vigenère Cipher for Polyalphabetic Encryption and Decryption

## Problem Statement

Write a C++ program to implement the Vigenère Cipher. The program should take a plaintext message and a keyword, encrypt the message by shifting each letter by a value determined by the keyword, and then decrypt the ciphertext back to the original plaintext.

## Introduction

The Vigenère Cipher is a polyalphabetic substitution cipher that uses a keyword to determine the shift for each letter. Unlike the Caesar Cipher (which shifts all letters by the same amount), the Vigenère Cipher uses different shifts for different letters based on a repeating keyword. This makes it much more resistant to frequency analysis.

It was invented by Giovan Battista Bellaso in 1553 and later misattributed to Blaise de Vigenère. It was known as "le chiffre indéchiffrable" (the unbreakable cipher) for centuries.

### Mathematical Formula

Encryption: `Cᵢ = (Pᵢ + Kⱼ) mod 26`

Decryption: `Pᵢ = (Cᵢ - Kⱼ) mod 26`

Where:
- **Pᵢ** = Plaintext letter position (0-25)
- **Cᵢ** = Ciphertext letter position
- **Kⱼ** = Keyword letter position (j = i mod keyword_length)
- The keyword repeats cyclically

### Key Concepts

- **Polyalphabetic:** Multiple alphabets are used (one per keyword letter).
- **Keyword:** Determines the shift pattern. Longer keywords provide better security.
- **Period:** The length of the keyword. After this many letters, the shift pattern repeats.
- **Tabula Recta (Vigenère Table):** A 26×26 grid showing all possible Caesar shifts.

### Example

Plaintext: `HELLO`, Keyword: `KEY`

K(10), E(4), Y(24) — keyword values

- H(7) + K(10) = 17 → R
- E(4) + E(4) = 8 → I
- L(11) + Y(24) = 35 mod 26 = 9 → J
- L(11) + K(10) = 21 → V
- O(14) + E(4) = 18 → S

Ciphertext: `RIJVS`

## Solution Explanation

The program works as follows:

1. **Input:** The user enters a plaintext string and a keyword.

2. **Encryption:**
   - Keep a keyword index counter starting at 0.
   - For each letter in the plaintext:
     - Get the shift value from the current keyword letter: `shift = keyword[index % keyword_length] - 'A'`.
     - Shift the plaintext letter forward by this amount: `C = (P + shift) mod 26`.
     - Increment the keyword index (only for letters, skip non-letters).
     - Non-letter characters pass through unchanged.

3. **Decryption:**
   - Same process, but shift backwards: use `shift = 26 - keyword_shift`.
   - The keyword index advances the same way.

### How the Code Works

The `vigenere(s, key, enc)` function handles both operations:
- For encryption, `shift` is taken directly from the keyword letter.
- For decryption, `shift` is `26 - keyword_letter_value`.
- The keyword index `kIdx` increments only for alphabetic characters, so non-letters don't disrupt the key alignment.

### Running the Program

```
Enter plaintext: Hello
Enter keyword: KEY
Encrypted: Rijvs
Decrypted: Hello
```
