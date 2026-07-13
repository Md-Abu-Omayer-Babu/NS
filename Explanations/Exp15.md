# Experiment 15: Implementation and Security Analysis of Knapsack Cryptosystem

## Problem Statement

Write a C++ program to implement the Knapsack (Merkle-Hellman) Cryptosystem. The program should generate a public key from a superincreasing knapsack sequence, encrypt a binary message by summing the public key values corresponding to 1-bits, and decrypt by solving the subset sum problem using the private superincreasing sequence.

## Introduction

The Merkle-Hellman Knapsack Cryptosystem was one of the earliest public-key cryptosystems, invented by Ralph Merkle and Martin Hellman in 1978. It is based on the subset sum problem (also known as the knapsack problem), which is NP-complete in general. However, a special case called the "superincreasing" subset sum problem can be solved easily.

### Mathematical Foundation

**Private Key:**
- A superincreasing sequence w₁, w₂, ..., wₙ (each element is greater than the sum of all previous elements)
- A modulus m > sum of all wᵢ
- A multiplier a where GCD(a, m) = 1

**Public Key:**
- bᵢ = (a × wᵢ) mod m for each i

**Encryption:**
- Convert the message to a binary string of length n.
- Compute C = sum of bᵢ for positions where the message bit = 1.

**Decryption:**
- Compute a⁻¹ mod m.
- Compute S = (C × a⁻¹) mod m.
- Solve the subset sum problem with the superincreasing sequence w:
  - Start from the largest element. If it fits in S, include it and subtract.
  - Continue to the smallest element.

### Superincreasing Sequence

A sequence is superincreasing if each element is greater than the sum of all previous elements:
- w₁ > 0
- w₂ > w₁
- w₃ > w₁ + w₂
- w₄ > w₁ + w₂ + w₃
- ...

This property makes the subset sum easy to solve greedily: start from the largest element and decide whether to include it based on whether it fits in the remaining sum.

### The Knapsack Problem

The general knapsack problem asks: given a set of numbers and a target sum, find a subset that sums to exactly the target. This is computationally hard (NP-complete). However, for superincreasing sequences, it's easy — this is the trapdoor that enables the cryptosystem.

### Example

Private key: w = [2, 3, 7, 14, 30] (superincreasing)
m = 61 (> 2+3+7+14+30 = 56)
a = 17 (GCD(17, 61) = 1)

Public key: b = [17×2 mod 61, 17×3 mod 61, 17×7 mod 61, 17×14 mod 61, 17×30 mod 61]
         = [34, 51, 58, 55, 22]

Message: "10101" (binary)
C = 34 + 58 + 22 = 114

Decrypt:
a⁻¹ mod 61 = 17⁻¹ mod 61 = 18 (since 17 × 18 = 306 = 5 × 61 + 1)
S = 114 × 18 mod 61 = 2052 mod 61 = 39

Solve subset sum with w = [2, 3, 7, 14, 30] and S = 39:
- 30 ≤ 39 → include 30, S = 9
- 14 > 9 → exclude
- 7 ≤ 9 → include 7, S = 2
- 3 > 2 → exclude
- 2 ≤ 2 → include 2, S = 0

Result: [1, 0, 1, 0, 1] = "10101" ✓

## Solution Explanation

The program works as follows:

1. **Input:** User enters the knapsack size, a superincreasing sequence w, modulus m, and multiplier a.

2. **Validation:**
   - Checks that the sequence is actually superincreasing (each element > sum of all previous).
   - Checks that m > sum of all wᵢ.
   - Checks that GCD(a, m) = 1.

3. **Public Key Generation:**
   - Compute bᵢ = (a × wᵢ) mod m for each element.
   - Display the public key.

4. **Encryption:**
   - User enters a binary string of length n.
   - Sum up all bᵢ where the corresponding bit is '1'.
   - Display the ciphertext (a single number).

5. **Decryption:**
   - Compute invA = a⁻¹ mod m.
   - Compute S = (C × invA) mod m.
   - Solve the superincreasing subset sum greedily from right to left:
     - If wᵢ ≤ current S, set bit i to '1' and subtract wᵢ from S.
     - Otherwise, set bit i to '0'.
   - Display the recovered binary string.

### How the Code Works

- `modInverse(a, m)` — Finds the modular inverse for decryption.
- `gcd(a, b)` — Checks that a and m are coprime.
- The greedy subset sum algorithm works because the sequence is superincreasing.
- A vector is used to store the knapsack values.

### Running the Program

```
Enter knapsack size: 5
Enter 5 superincreasing values: 2 3 7 14 30
Enter modulus m (> 56): 61
Enter multiplier a (coprime with 61): 17
Public key: 34 51 58 55 22
Enter binary message (5 bits): 10101
Encrypted: 114
Decrypted: 10101
```
