# Experiment 14: Design and Implementation of Rabin Cryptosystem

## Problem Statement

Write a C++ program to implement the Rabin Cryptosystem. The program should take two primes (each congruent to 3 mod 4) as the private key, encrypt a numeric message by squaring it modulo n, and then decrypt using the Chinese Remainder Theorem to recover the original message from four possible candidates.

## Introduction

The Rabin Cryptosystem is a public-key cryptosystem invented by Michael O. Rabin in 1979. Its security is based on the difficulty of factoring integers — specifically, it can be proven that breaking Rabin is as hard as factoring large composite numbers. This is a stronger security guarantee than RSA (which is based on the difficulty of factoring, but is not proven to be equivalent).

### Mathematical Foundation

**Key Generation:**
1. Choose two large primes p and q, both ≡ 3 mod 4
2. Compute n = p × q

**Public key:** n
**Private key:** (p, q)

**Encryption:** `C = M² mod n`

**Decryption:** 
Compute square roots of C modulo p and q:
- mₚ = C^((p+1)/4) mod p
- m_q = C^((q+1)/4) mod q

Then combine using the Chinese Remainder Theorem to get four possible square roots.

### The 3 mod 4 Requirement

When a prime p ≡ 3 mod 4, the square root of C modulo p can be computed efficiently using the formula:
- `mₚ = C^((p+1)/4) mod p`

This formula only works when p ≡ 3 mod 4, which is why we require both primes to satisfy this condition.

### Ambiguity (Four Possible Messages)

The decryption process always produces four possible plaintexts. The correct message must be identified by the recipient using additional context or redundancy (e.g., the message might contain a known pattern).

The four candidates are: `r₁`, `r₂`, `n - r₁`, `n - r₂`

### Example

p = 7 (≡ 3 mod 4), q = 11 (≡ 3 mod 4)
n = 77

Message M = 10
C = 10² mod 77 = 100 mod 77 = 23

Decrypt:
mₚ = 23^((7+1)/4) mod 7 = 23² mod 7 = 2² mod 7 = 4
m_q = 23^((11+1)/4) mod 11 = 23³ mod 11 = 1³ mod 11 = 1

Using CRT:
r₁ = (4 × 11 × 11⁻¹ mod 7 + 1 × 7 × 7⁻¹ mod 11) mod 77
  = (4 × 11 × 2 + 1 × 7 × 8) mod 77  [11⁻¹ mod 7 = 4, wait...]
  
Let me recalculate: 7⁻¹ mod 11 = 8 (since 7 × 8 = 56 = 5 × 11 + 1)
11⁻¹ mod 7 = 2 (since 11 × 2 = 22 = 3 × 7 + 1)

r₁ = (4 × 11 × 2 + 1 × 7 × 8) mod 77 = (88 + 56) mod 77 = 144 mod 77 = 67
r₂ = (4 × 11 × 2 - 1 × 7 × 8) mod 77 = (88 - 56) mod 77 = 32 mod 77 = 32
r₃ = 77 - 67 = 10
r₄ = 77 - 32 = 45

Four possible messages: 67, 32, 10, 45
Original message: 10 ✓

## Solution Explanation

The program works as follows:

1. **Input:** User enters two primes p and q (p ≡ 3 mod 4, q ≡ 3 mod 4).

2. **Validation:** The program checks that both primes are indeed ≡ 3 mod 4.

3. **Encryption:**
   - Compute n = p × q.
   - Compute C = (M × M) mod n (just square the message).

4. **Decryption:**
   - Compute mₚ = C^((p+1)/4) mod p.
   - Compute m_q = C^((q+1)/4) mod q.
   - Use Chinese Remainder Theorem to combine:
     - r₁ = (mₚ × q × q⁻¹ mod p + m_q × p × p⁻¹ mod q) mod n
     - r₂ = (mₚ × q × q⁻¹ mod p - m_q × p × p⁻¹ mod q) mod n
     - If negative, add n.
   - r₃ = n - r₁, r₄ = n - r₂
   - Display all four candidates.

### How the Code Works

- `modPow(b, e, m)` — Fast exponentiation for computing mₚ, m_q.
- `modInverse(a, m)` — Finds modular inverse needed for CRT.
- The CRT formula combines the two modular square roots into the modulo n result.
- The program checks if the original message matches any of the four candidates.

### Running the Program

```
Enter prime p (≡ 3 mod 4): 7
Enter prime q (≡ 3 mod 4): 11
Enter message (number < 77): 10
Encrypted: 23
Possible plaintexts: 67, 32, 10, 45
Original message: 10 [matched]
```
