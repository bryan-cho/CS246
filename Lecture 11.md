# Lecture 11 - Oct. 20, 2015

Preprocessor, Separate Compilation.

## Conditional Compilation

e.g.)
Native Windows application requires `winMain()`
Linux needs `main()`

```cpp
#define Unix 1
#define Windows 2

//Comment out only one of the following two lines and run
//g++ -E -P condcompile.cc

//#define OS Unix 
#define OS Windows


#if OS == Unix
int main(){ 

#elif OS == Windows 
int winMain (){

#endif

/*
 * Shared code comes here
 */
 return 0;
}
```

We uncomment the line that corresponds to the OS we want to compile this program for.

```cpp
#define Unix 1
#define Windows 2

//call using either
// g++ -DOS=Unix -E -P condcompile.cc
// g++ -DOS=Windows -E -P condcompile.cc

#if OS == Unix
int main(){ 

#elif OS == Windows 
int WinMain (){

#endif

/*
 * Shared code comes here
 */
 return 0;
}
```

We can set what the OS is from the command line before we compile the code.

```cpp
//call using either
// g++ -DUnix -E -P condcompile.cc
// g++ -DWindows -E -P condcompile.cc

#ifdef Unix 
int main(){ 
#endif

#ifdef Windows 
int winMain (){
#endif

/*
 * Shared code comes here
 */
 return 0;
}
```

We can also get rid of those comparisons and check if `Unix` or `Windows` is defined.

This is particularly useful for debugging.

```cpp
#include <iostream>
using namespace std;

int main() {
  #ifdef DEBUG    
     cout << "setting x=1" << endl;  
  #endif
  int x = 1;
  while (x < 10) {
    ++x;
    #ifdef DEBUG
      cout << "x is now " << x << endl;
    #endif
  }
  cout << x << endl;
}
```

We can conditionally compile this code to have debugging output when we define DEBUG before we compile.

## Separate Compilation

Interface file (.h)

* Type definitions
* Function headers

Implementation file (.cc)

* Implementation of functions

To compile multiple files:

1. `g++ *.cc`
2. `g++ program1.cc program2.cc`

Separate compilation is particularly useful for large projects.

We would not need to compile the entire project each time a minor change is made to a smaller module.

By default g++:

`Preprocessor --> compiler --> linker`

This causes a problem if we want to compile just one module that is part of a larger program.

We fix this by doing:

`g++ -c program.cc`

This produces an object file (.o). It contains:

* compiled code
* lists the "needs"
* lists the "haves" (definitions)

Once we have all the object files, we can call `g++ program1.o program2.o ...`

The linker now ensures that all the "needs" are satisfied.

If all "needs" are satisfied it will produce an executable.

### Notes

Use keyword `extern` when declaring variables in headers (.h)

## Include Guard

In program1.h:
```cpp
#ifndef PROGRAM1_H <-- not defined
#define PROGRAM1_H <-- defines it now

code

#endif

Subsequent includes will not declare the same code
```

This makes sure that once this header has been defined once, the same declarations will never be included in the program again.
