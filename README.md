#

 
## Motivation

You can install it from [here](https://apt.llvm.org/) (for Ubuntu and Debian only).


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
Default target is `driver`, it produces `driver` binary file in current (build) directory
