## Important!!10!
**LLVM version should be >= 17.0**

You can install it from [here](https://apt.llvm.org/) (for Ubuntu and Debian only).

Rename your remote repo from **origin** to something else!
ANTLR4 also uses *origin* for it's repo and it otherwise causes errors. 

## Getting started
```bash
$ mkdir build
$ cd build
$ cmake ../
$ make
```
Default target is `driver`, it produces `driver` binary file in current (build) directory
