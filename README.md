# ⚡️ Custom IR Compiler
This is a compiler for our made-up programming language inspired by C++ and Python.
Grammar of this language is defined in file ```Expr.g4```.
See sample program in ```input.txt```
 
## Motivation
Welcome to our custom compiler project, the culmination of our efforts in the [MIPT Compilers Course](https://github.com/akhtyamovpavel/CompilersCourse/tree/master).
Our primary goal throughout this endeavor has been to gain a deep understanding of the intricate process through which program text in a programming language is seamlessly transformed into efficient machine code.

Embarking on this journey, we commenced by constructing an interpreter leveraging the power of ANTLR4. This initial phase allowed us to grapple with the nuances of language parsing and interpretation, providing a solid foundation for what was to come.

As our proficiency grew, we transitioned from interpreter to compiler, harnessing the robust LLVM framework.This transformation marked a significant milestone as we delved into the realms of code generation and the intricate dance between abstract syntax trees and machine code emission.

## Setting this up
These commands can be used to setup CIRCT project:
1) **Install LLVM 17.0**, for Linux distros one can find it [here](https://apt.llvm.org/). Other dependencies are c++ compiler (we recommend **Clang**) and **Make**.

2) **Check out Testing repo.**  Testing contains ANTLR4 as a git
submodule.  ANTLR is installed on first run of CMake. 
```bash
$ git clone git@github.com:eg0rmeister/testing.git
$ cd testing
```
```bash
$ mkdir build
$ cd build
$ cmake ../
$ make
```

3) **Build and test compiler:**
```bash
$ cd build
$ cmake ..
$ make
```
*Note:*  Default target is `driver`, it produces `driver` binary file in current (build) directory

