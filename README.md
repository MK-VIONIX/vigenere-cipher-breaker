# Vigenère Cipher Breaker (Repeating-Key XOR Cryptanalysis)

This project implements a **Vigenère cipher breaker** using statistical cryptanalysis.
The program automatically detects the key length, recovers the key, and decrypts the ciphertext.

The ciphertext is assumed to be **Base64 encoded** and encrypted using a **repeating-key XOR (Vigenère cipher)**.

---

## Features

* Base64 decoding
* Hamming distance calculation
* Automatic key size detection
* Frequency analysis scoring
* Single-byte XOR key recovery
* Repeating-key XOR decryption
* Plaintext output written to a file

---

## How It Works

The program breaks the cipher using the following steps:

### 1. Base64 Decoding

The ciphertext is read from a file and decoded from Base64 to raw bytes.

### 2. Key Size Detection

For key sizes from **2 to 40**, the program computes the **normalized Hamming distance** between consecutive blocks.

The key size with the **smallest normalized distance** is selected as the most probable key length.

### 3. Block Transposition

The ciphertext is split into blocks where each block contains bytes encrypted by the **same key byte**.

Example:

Key = `ABC`

Ciphertext bytes:

```
C0 C1 C2 C3 C4 C5 C6 C7 C8
```

Transposed blocks:

```
Block 0 → C0 C3 C6
Block 1 → C1 C4 C7
Block 2 → C2 C5 C8
```

Each block is now equivalent to a **single-byte XOR cipher**.

### 4. Single-Byte XOR Cracking

Each block is decrypted by trying **all 256 possible key values**.

A scoring function based on **English letter frequency** selects the best key byte.

### 5. Key Recovery

All recovered key bytes are combined to reconstruct the **full Vigenère key**.

### 6. Final Decryption

The ciphertext is decrypted using repeating-key XOR:

```
plaintext[i] = ciphertext[i] XOR key[i mod key_length]
```

---

## File Structure

```
.
├── base_64.txt     # Input ciphertext (Base64 encoded)
├── output.txt      # Decrypted plaintext output
├── vigenere.cpp    # Cipher breaker implementation
└── README.md
```

---

## Compilation

Compile using **g++**:

```
g++ vigenere.cpp -o breaker
```

---

## Usage

Place the encrypted Base64 ciphertext inside:

```
base_64.txt
```

Run the program:

```
./breaker
```

The decrypted plaintext will be written to:

```
output.txt
```

---

## Example Workflow

1. Provide Base64 encoded ciphertext
2. Program estimates key size
3. Program recovers the key
4. Ciphertext is decrypted
5. Plaintext is saved to `output.txt`

---

## Concepts Used

* Vigenère Cipher
* Repeating-Key XOR
* Cryptanalysis
* Hamming Distance
* Frequency Analysis
* Base64 Encoding

---

## Learning Goal

This project was built as part of learning **practical cryptography and classical cipher attacks**, inspired by the **Cryptopals cryptography challenges**.

---

## Author

Mohit Kumawat
