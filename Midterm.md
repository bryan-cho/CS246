# Midterm - Oct. 29, 2015

On the exam:

Preprocessor

Separate Compilation

Constructor

Copy constructor

Shell script (Similar to runSuite)

- Shell
- Linux File System, Special Directories
- cd, pwd, ls, echo, rm, 
- Globbing patterns
- cat
- Input/Output Redirection
- Pipes
- egrep
- File Permissions (chmod)
- Shell Variables ($PATH)
- Shell Scripts
- Command Line Arguments to a script
- $#, $?, /dev/null, $0
- script functions
- if statement
- While loop
- for loop
- Testing
- C++
- Hello World
- Compiling/Executing C++ programs
- Stream Objects (cin, cout, cerr)
- I/O Operators (>>, <<)
- cin.fail(), cin.eof()
- implicit conversion of a stream to void* (e.g. cin to void*)
- << and >> are binary operators: must produce an expression
- << and >> cascading
- cin.ignore(), cin.clear() 
- std::string
- Semantics of reading from cin
- I/O Manipulators: hex, dec, showpoint, setprecision , boolalpha, header <iomanip>
- Stream Abstraction for files
- header <fstream>, ifstream, ofstream
- when is a file opened, when is it closed
- Stream abstraction for strings
- header <sstream>, istringstream, ostringstream
- Converting a string to an integer
- comparison between readInts5.cc and readsIntSS.cc
- Strings in C++
- std::string is not the same as a c-style string
- string operations: concat, length, comparisons, length
- Default Arguments 
- Function Overloading
- Review: Declaration Before Use
- Review: Pointers
- Review: Arrays
- Structs in C vs structs in C++
- Review: Constants (see review slides 1151/lectures/ReviewSlides)
- Review: Passing by Value, Passing a pointer (see review slides 1159/lectures/ReviewSlides)
- References 
- Things you can and cannot do with references
- Pass by reference
- Why does cin >> x work in C++ when in C we had to do scanf("%s",&x)
- Pass by Value vs Passing a pointer vs Pass by reference: pros and cons of each
- Dynamic Memory Allocation: new and delete
- Review Slides: Stack vs Heap Allocation 
- Operator Overloading
- Examples: Vec, Grade
- The C and C++ Preprocessor
- #include: copy and paste
- #define: search and replace
- Using #define for Conditional Compilation (OS example, DEBUG example)
- Separate Compilation (lectures/c++/separate) 
- C++ Classes
- What is a class, what is an object, what are "functions" inside classes
- Distinction between functions and methods
- Initializing Objects
- C Style Initialization
- Constructors
- Built-in 0 parameter ctor
- Initializing const and reference fields
- Steps that occur when an object is created
- Member Initialization List (MIL)
- Advantages of MIL
- Copy Ctor
- default ctor (shallow copy)
- deep copy ctor
- When to use deep copy
- Places where a copy ctor is called
