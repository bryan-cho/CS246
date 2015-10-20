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
