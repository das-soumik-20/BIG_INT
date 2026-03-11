# BigInt – Arbitrary Precision Integer Library

## Overview

This project implements an **arbitrary-precision integer (BigInt) library in C++** capable of performing arithmetic operations on integers larger than the limits of built-in data types such as `long long`.

The implementation stores numbers using a **block representation with base (10^9)** to efficiently perform large integer computations while minimizing memory usage and improving arithmetic performance.

## Features

* Supports **very large integers** beyond 64-bit limits
* Handles **positive and negative numbers**
* Implements core arithmetic operations:

  * Addition
  * Subtraction
  * Multiplication
* Uses **vector-based block storage** for efficient operations
* Implements **manual carry and borrow propagation**
* Provides a **command-line interface** to test arithmetic operations

## Internal Representation

Each integer is stored as blocks of digits in **base (10^9)**.

Example representation:

Number

```
1234567890123456789
```

Stored as blocks:

```
[23456789, 345678901, 1]
```

This reduces the number of elements needed for computation compared to storing single digits.

## Class Structure

### BigInt Class

The `BigInt` class contains:

* `vector<int> blocks`
  Stores integer blocks in base (10^9)

* `bool negative`
  Tracks whether the number is negative

### Main Operations

| Function              | Description                   |
| --------------------- | ----------------------------- |
| `addMagnitude()`      | Adds absolute values          |
| `subtractMagnitude()` | Subtracts absolute values     |
| `multiplyMagnitude()` | Multiplies absolute values    |
| `add()`               | Handles signed addition       |
| `subtract()`          | Handles signed subtraction    |
| `multiply()`          | Handles signed multiplication |
| `comparison()`        | Compares magnitudes           |

## Example Usage

Program menu:

```
1. Add
2. Subtract
3. Multiply
Enter your option:
```

Example input:

```
Enter 1st operand: 123456789123456789
Enter 2nd operand: 987654321987654321
```

Output:

```
1111111111111111110
```

## Technologies Used

* C++
* STL (`vector`, `string`)
* GCC compiler

## Learning Outcomes

Through this project I learned:

* Implementation of **arbitrary precision arithmetic**
* Efficient **number representation using blocks**
* **Manual arithmetic algorithms** (carry/borrow handling)
* Designing **custom numeric classes**
* Managing **large integer computations**

## Future Improvements

* Implement **division**
* Implement **Karatsuba multiplication**
* Add **operator overloading (`+ - *`)**
* Support **modular arithmetic**

## Author

Soumik Das
Computer Science Engineering
VNIT Nagpur

GitHub:
https://github.com/das-soumik-20
