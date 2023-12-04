
---

# Generic Vector Structure in C

[中文](README-zh.md)

This repository contains an implementation of a generic Vector structure in C, designed to mimic the behavior and functionality of the Vector class commonly used in C++. The Vector structure is capable of storing elements of any data type, similar to how templates work in C++. This implementation provides a useful example of how to achieve generic programming in C, a language that does not natively support templates.

## Features

- **Generic Storage**: The Vector structure uses `void*` to store elements, allowing for the storage of any data type.
- **Dynamic Resizing**: Automatically expands or shrinks in size depending on the number of elements, ensuring efficient use of memory.
- **Various Operations**: Supports operations such as insertion, deletion, searching, sorting, and more.
- **Custom Memory Management**: Includes manual handling of memory allocation and deallocation for flexibility.

## Comparison with C++ Vector Class

In addition to the C implementation, this repository also includes a C++ file, derived from the Data Structure curriculum of Tsinghua University by Dr. Deng. This file serves as a comparison to illustrate how similar functionality is achieved in C++ using templates, which offer type safety and ease of use. The comparison highlights the differences and similarities in the implementation and usage of generic programming concepts in both languages.

## Usage

The repository provides clear examples and usage patterns for the Vector structure. Users can see how to initialize a vector, add elements, access elements, and perform various operations in a manner that parallels the usage of vectors in C++.
