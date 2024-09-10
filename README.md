# Encode-Decode Project

## Overview

This project implements a custom encoding and decoding system. The encoding algorithm compresses numerical data into a compact sequence of bits, and the decoding algorithm retrieves the original data from the encoded sequence. The encoded sequence is stored using a combination of bitwise operations and a custom bit length sequence.

## Project Structure

The project consists of the following files:

- `run.c`: Main file for running the encoding/decoding process.
- `encode.c`: Contains the `encode` function, responsible for encoding a number into a sequence.
- `decode.c`: Contains the `decode` function, which decodes an encoded sequence to recover the original number.
- `helper.c`: Provides helper functions for managing the linked list structure and bit manipulation.

## Data Structures

- **Union `decStore`**: A union that stores the data as both `unsigned long long int` and its byte representation using an array of `unsigned char[]`.
- **Linked List (`sLinkedList`)**: A singly linked list is used to store the sequence of bit lengths for encoding purposes.

## Functions

### Encoding (`encode.c`):
- **`unsigned char encode(unsigned char *in, unsigned char length, unsigned char *out)`**:
    - Encodes the input data (`in`) into an output array (`out`), returning the number of bits required for the encoded sequence.
    - Uses the linked list to store bit sequences for encoding.

### Decoding (`decode.c`):
- **`unsigned long long int decode(unsigned char *out)`**:
    - Decodes an encoded sequence from `out` and returns the original number by reversing the encoding process.

### Helper Functions (`helper.c`):
- **Linked List Creation**: Functions to create and manage the linked list that holds bit sequences.
- **Bit Calculation**: Functions to calculate the number of bits required to store a number.

## Compilation and Execution

### Final Build Command

To compile the entire project, use the following command:

```bash
make
```

### Running the Program

After compilation, run the program as follows:

```bash
./run 
```

This will execute the encoding and decoding process defined in `run.c`, where encoded data is generated, and the original value is retrieved through decoding.

---

## How Encoding and Decoding Work

### Encoding:
1. The number is encoded into a custom sequence using the linked list to store bit lengths.
2. The sequence of bits is stored in a compact format using bitwise operations.
3. The output is a sequence of bytes, where each byte can store parts of the encoded sequence.

### Decoding:
1. The decoding algorithm reverses the encoding process, reading the sequence bit by bit.
2. It retrieves the original number by interpreting the sequence of bits according to the encoded length and structure.
