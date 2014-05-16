# CppADCodeGen #

CppADCodeGen performs *hybrid Automatic Differentiation* (AD), that is, uses 
operator-overloading and produces source-code. Such source-code can be 
statically compiled at runtime using an existing compiler and linked dynamically 
or, alternatively, go through a JIT compilation using Clang/LLVM.

CppADCodeGen can also be used to perform differentiation index reduction of 
Differential Algebraic Equations (DAE) through the Pantelides and Dummy 
Derivatives methods.

CppADCodeGen is built on top of the [CppAD](http://www.coin-or.org/CppAD) 
library, which is a header only C++ AD library using operator overloading.

## License ##

CppADCodeGen is available with both the *EPL* and *GPL* licenses 
(suitable for both open-source and closed-source commercial projects).
See epl-v10.txt and gpl3.txt for a copy of the licenses.

## Requirements ##

CppADCodeGen is a C++11 header only library so there aren't many dependencies:

 - *CppAD* (2014)
 - A *C++11* compiler (such as GCC and Clang).
 - Clang/LLVM 3.2 or 3.4 (only for JIT compilation)
 - Eigen 3 (only for DAE differentiation index reduction)

Runtime compilation and dynamic linking:
 - Linux (it might be very easy to support other OSes but it is not implemented yet)

## Installing ##

### General installation ###

Just copy the contents of the folder include to anywhere you would like to 
include from.

### Debian/Ubuntu ###

A debian installation package can be created at the root of the project.
Typically you can create the installer by just typing:

    dpkg-buildpackage

It will create a debian package outside the project's folder.

## Using CppADCodeGen ##

See the [wiki](https://github.com/joaoleal/CppADCodeGen/wiki).

The folder example includes some simple usage cases.

---

## Repository Content

|Directories |  Description                                                    |
|------------|-----------------------------------------------------------------|
|bin         | Helper shell and sed scripts used for CppAD development.        |
|bug         | Directory containing demonstration of known bugs (may be empty) |
|debian      | Debian package creation files (Linux).                          |
|include     | The CppADCodeGen header files.                                  |
|example     | CppADCodegen example files are here.                            |
|pkgconfig   | pkg-config support files.                                       |
|test        | Contains tests for CppADCodeGen.                                |
|speed       | Contains some benchmarks for CppADCodeGen.                      |


| Files         |  Description                                                 |
|---------------|--------------------------------------------------------------|
|AUTHORS        | Statement of authorship and copyright.                       |
|CMakeLists.txt | CppADCodeGen CMake input file.                               |
|COPYING        | Statement of user license to use software.                   |
|doxyfile.in    | Control file for CppADCodeGen developer documentation.       |
|epl-v10.txt    | A copy of the Eclipse Public License version 1.              |
|gpl3.txt       | A copy of the GNU General Public License version 3.          |
|INSTALL        | Points to this file.                                         |