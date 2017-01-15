# CVector
[![Build Status](https://travis-ci.org/tschuchortdev/cvector.svg?branch=master)](https://travis-ci.org/tschuchortdev/cvector)

CVector simple generic vector implemented in C

## Installation

Simply copy the files `vector.h` and `vector.c` in your source directory.


## Usage

`Vector` works for all types and can save copies, you don't have to allocate the elements on the heap yourself.

    Vector vec = INIT_VECTOR(int);
    
    int a = 5;
    vectorAdd(&vec, &a);
    
    int b = ((int*) vec.data)[0];
    // or
    int c = *(int*) vectorGet(&vec, 0);
    
    //dont forget to free the vector
    vectorDestroy(&vec);
    
 
 
