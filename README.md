# CVector
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/62b547e56ed746958f06cc1dfd770d7c)](https://www.codacy.com/app/t-schuchort/cvector?utm_source=github.com&utm_medium=referral&utm_content=tschuchortdev/cvector&utm_campaign=badger)
[![Build Status](https://travis-ci.org/tschuchortdev/cvector.svg?branch=master)](https://travis-ci.org/tschuchortdev/cvector) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) 
[![Build Status](https://ci.appveyor.com/api/projects/status/github/tschuchortdev/cvector?branch=master&svg=true)](https://ci.appveyor.com/project/tschuchortdev/cvector/branch/master)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](https://github.com/tschuchortdev/cvector/issues)


CVector simple generic vector implemented in C

## Installation

Simply copy the files `vector.h` and `vector.c` in your source directory.


## Usage

`Vector` works for all types and can save copies, you don't have to allocate the elements on the heap yourself.

```C
Vector vec = INIT_VECTOR(int);

int a = 5;
vectorAdd(&vec, &a);

int b = ((int*) vec.data)[0];
// or
int c = *(int*) vectorGet(&vec, 0);

//dont forget to free the vector
vectorDestroy(&vec);
```
 
 
