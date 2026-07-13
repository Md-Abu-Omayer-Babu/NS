# Experiment 12: Design and Implementation of RSA Public-Key Cryptosystem

## Problem Statement

Write a C++ program to implement the RSA (Rivest-Shamir-Adleman) cryptosystem. The program should generate public and private keys from two prime numbers, encrypt a numeric message using the public key, and decrypt it using the private key.

## Introduction

RSA is one of the first practical public-key cryptosystems, invented in 1977 by Ron Rivest, Adi Shamir, and Leonard Adleman. Unlike symmetric ciphers where encryption and decryption use the same key, RSA uses a pair of keys: a public key for encryption and a private key for decryption.

The security of RSA relies on the practical difficulty of factoring the product of two large prime numbers.

### Mathematical Foundation

**Key Generation:**
1. Choose two large primes: p, q
2. Compute: n = p × q
3. Compute: φ(n) = (p-1) × (q-1)
4. Choose e where 1 < e < φ(n) and GCD(e, φ(n)) = 1
5. Compute d = e⁻¹ mod φ(n) (modular inverse)

**Public key:** (e, n)
**Private key:** (d, n)

**Encryption:** `C = Mᵉ mod n`

**Decryption:** `M = Cᵈ mod n`

### Why RSA Works

Due to Euler's theorem: `M^(ed) mod n = M^(1 + k×φ(n)) mod n = M mod n`

So encryption followed by decryption recovers the original message.

### Example (with very small numbers)

p = 11, q = 13
n = 143
φ(n) = 10 × 12 = 120
Choose e = 7 (GCD(7, 120) = 1)
d = 7⁻¹ mod 120 = 103 (since 7 × 103 = 721 = 6 × 120 + 1)

Public key: (7, 143)
Private key: (103, 143)

Message M = 9
C = 9⁷ mod 143 = 48
M = 48¹⁰³ mod 143 = 9 ✓

## Solution Explanation

The program works as follows:

1. **Input:** User enters two prime numbers p and q.

2. **Key Generation:**
   - Compute n = p × q and phi = (p-1) × (q-1).
   - Find e: start from 2, increment until GCD(e, phi) = 1.
   - Compute d as the modular inverse of e modulo phi.

3. **Encryption:**
   - The user enters a numeric message M (must be less than n).
   - Compute C = Mᵉ mod n using modular exponentiation.

4. **Decryption:**
   - Compute M = Cᵈ mod n using modular exponentiation.

### Modular Exponentiation

The program uses the fast exponentiation method (also called binary exponentiation or square-and-multiply):
- Convert the exponent to binary.
- For each bit: square the current result, and if the bit is 1, multiply by the base.
- At each step, take mod n to keep numbers manageable.

This is much faster than naive repeated multiplication.

### How the Code Works

- `modPow(b, e, m)` — Computes bᵉ mod m using binary exponentiation.
- `modInverse(a, m)` — Finds x such that (a × x) % m = 1.
- `gcd(a, b)` — Euclidean algorithm.
- In `main()`: generate keys, encrypt, decrypt.

### Running the Program

```
Enter prime p: 11
Enter prime q: 13
Public key (e, n): (7, 143)
Private key (d, n): (103, 143)
Enter message (as number < 143): 9
Encrypted: 48
Decrypted: 9
```

### Note

This implementation uses small primes for demonstration. Real-world RSA uses primes hundreds of digits long (2048 bits or more).
