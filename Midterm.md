# Midterm - Oct. 29, 2015

On the exam:

Preprocessor

Separate Compilation

Constructor

Copy constructor

Shell script (Similar to runSuite)

- Shell
    * Interface to OS
- Linux File System, Special Directories
    * `.` - current directory
    * `..` - previous directory
- cd, pwd, ls, echo, rm
    * `cd` - Change Directory
    * `pwd` - Present working directory
    * `ls` - List directory contents
        * `-l` in-depth
        * `-r` reverse
        * `-t` chronological order (newest to oldest)
        * `-a` display hidden files
    * `echo` - Write to stdout
    * `rm` - Remove
- Globbing patterns
    * `?` - zero or one occurrences
    * `*` - zero or more occurrences
    * `+` - one or more
    * `^` - starts with
    * `$` - ends with
    * `{3}` - exactly 3
    * `{3,}` - 3 or more
    * `{3,5}` - between 3 and 5
    * `.` - any character
    * `(a|b)` - a or b
    * `[abc]` - in a, b, or c
    * `[^abc]` - not in a, b, or c
    * `[a-z]` - a to z
    * `[0-9]` - 0 to 9
- cat
    * `cat` - prints contents of a file
- Input/Output Redirection
    * `>` - output redirection
    * `<` - input redirection
    * `2>` - stderr redirection
    * `&>` - stdout and stderr redirection
    * `>>` - append (can be used with any of the output redirections above
- Pipes
    * `|` use this to send shit between programs
- egrep
    * You can match regex patterns using this
- File Permissions (chmod)
    * `a/u/g/o` - all/user/group/other
    * `+/-` - add/remove
    * `r/w/x` -read/write/execute
- Shell Variables ($PATH)
    * `$PATH` - pwd
    * `x=1` - set x to 1
    * `x=$((x+1))` - add 1 to x
- Shell Scripts
    * `#!/bin/bash` 
- Command Line Arguments to a script
    * `$1, $2, ..., $n` - arguments
    * `$@` - sequence of strings that contains the arguments
    * `shift` - shift arguments one to the left
- $#, $?, /dev/null, $0
    * `$#` - number of arguments
    * `$?` - exit code of previously run program
    * `/dev/null` - black hole
    * `$0` - script itself
- backticks
    * \` - this means, execute the command and return the output as a string to where it was called  
- script functions

 ```bash
functionName () {
    # You can put anything in here 
}
```

- if statement

```bash
if [ $# -lt "3" ]; then 
    echo "Usage ${0} arg1 arg2 ..."
fi
```

- While loop

```bash
while [ ${x} -le $1 ]
do                       <-- do marks the start of execution body
    echo ${x}
    x=$((x + 1))
done < "file"            <-- done marks end of loop
```

- for loop
    * Note that the `x` will just be iterating over the elements which will be strings

```bash
for x in a b c d;        <-- we can also use globbing patterns here
do                       <-- do marks the start of execution body
done                     <-- done marks end of loop
```

- Testing
    * Blackbox
    * Edge cases
    * Positive/Negative
    * Corner cases

- C++
- Hello World
- Compiling/Executing C++ programs
    * `g++ file -o outputFileName`

- Stream Objects (cin, cout, cerr)
    * `cin` - stdin
    * `cout` - stdout
    * `cerr` - stderr

- I/O Operators (>>, <<)
    * `>>` input
    * `<<` output

- cin.fail(), cin.eof()
    * `cin.fail()` - the input failed (e.g. string -> int)
    * `cin.eof()` - the input gave EOF

- implicit conversion of a stream to void* (e.g. cin to void*)
    * `cin == true` - if `!(cin.fail())`
    * `cin == false` - if `cin.fail()`

- << and >> are binary operators: must produce an expression
    * `>>` and `<<` operators should always return a reference to an `ostream` object

- << and >> cascading
    * `>>` and `<<` can cascade operations because it returns a reference to an `ostream` object

- cin.ignore(), cin.clear() 
    * `cin.ignore()` - this will ignore the next input
    * `cin.clear()` - removes the `cin.fail()` flag

- std::string
    * string type built in to C++
    * works like how strings work in any other language

- Semantics of reading from cin
    * `CTRL+D` - EOF
    * `CTRL-C` - KILL

- I/O Manipulators: hex, dec, showpoint, setprecision , boolalpha, header <iomanip>
    * `dec` - decimal values
    * `hex` - show values in hex
    * `left` - left align
    * `right` - right align
    * `showpoint` - print decimal points
    * `setprecision` - set sig figs
    * `boolalpha` - prints `true/false` over `1/0`
    * `#include <iomanip>`

- Stream Abstraction for files
- header <fstream>, ifstream, ofstream
    * Initialize with `ifstream("filename")`
    * You can output to a file using `ofstream`
    * Can read one word at a time using `>>`

- when is a file opened, when is it closed
    * Stream closes when it goes out of scope
    * Stream closes when you call `stream.close()`
    * Can check if it is open with `stream.open()`

- Stream abstraction for strings
- header <sstream>, istringstream, ostringstream
    * Initialize with `istringstream(string)`
    * Output to strings

- Converting a string to an integer
    * Use `istringstream(string) >> int`

- comparison between readInts5.cc and readsIntSS.cc
   
- Strings in C++
- std::string is not the same as a c-style string
- string operations: concat, length, comparisons, length
    * Can use `+/</>/==`

- Default Arguments 
    * Set `argument = default value`

- Function Overloading
    * Same name, different parameters

- Review: Declaration Before Use
- Review: Pointers
- Review: Arrays
- Structs in C vs structs in C++
    * Can define methods    

- Review: Constants (see review slides 1151/lectures/ReviewSlides)
- Review: Passing by Value, Passing a pointer (see review slides 1159/lectures/ReviewSlides)
- References 
    * Can't be null
    * Can only be assigned to lvalues

- Things you can and cannot do with references
    * Can't change them

- Pass by reference
    * Take a reference as a param

- Why does cin >> x work in C++ when in C we had to do scanf("%s",&x)
    * operator overloading

- Pass by Value vs Passing a pointer vs Pass by reference: pros and cons of each
ByVal - pros:
    * safe
    * thread safe

ByVal - cons:
    * calls copy constructor
    * memory expensive

ByPointer - pros: 
    * does not call constructor
    * pointers can be null
    * flexible, can do anything with them

ByPointer - cons:
    * least safe

ByRef - pros:
    * does not call copy ctor
    * memory efficient

ByRef - cons:
    * can't be null
    * can't change address
    
- Dynamic Memory Allocation: new and delete
- Review Slides: Stack vs Heap Allocation 
- Operator Overloading
    * `int operator+(const int &a, const int &b)`
    
- Examples: Vec, Grade
- The C and C++ Preprocessor
- \#include: copy and paste
    * copy and paste

- \#define: search and replace
    * search and replace

- Using #define for Conditional Compilation (OS example, DEBUG example)
    * `#if VALUE #elif VALUE #else #endif`
    * `#ifdef VAR #ifndef VAR #endif`
    * `-D` can be used to define before we compile
    * `-DVAR="VAL"`

- Separate Compilation (lectures/c++/separate) 
    * Compile using `-c` to get `.o` files
    * We can get executable by just compiling the `.o` files

- C++ Classes
    * class is a struct with functions inside it
    * methods in structs/classes    

- What is a class, what is an object, what are "functions" inside classes
    * method
- Distinction between functions and methods
- Initializing Objects
    * Space allocated
    * Field initialization
    * Constructor body
    * We initialize using constructor
    * We can initialize an object that has only the default constructor c-style

- C Style Initialization
- Constructors
- Built-in 0 parameter ctor
- Initializing const and reference fields
    * Use of MIL
- Steps that occur when an object is created
    * Space allocated
    * Field initialization
    * Constructor body

- Member Initialization List (MIL)
- Advantages of MIL
    * If data is `const`, then we must use MIL as we cannot use the constructor body to assign a value to a `const`.
    * We also say the same for references.
    * Statically allocated struct (not a primitive type) e.g.) object needs to be initialized
        * If we do this initialization in the constructor body, the default constructor will be called twice
        * This is because at stage 2 of initializing an object, we initialize fields which calls the default constructor for any non primitive types
- Copy Ctor
- default ctor (shallow copy)
- deep copy ctor
    * Remember to dereference pointers when trying to deep copy
    * Check for condition where pointer is null before dereferencing (in notes)
- When to use deep copy
- Places where a copy ctor is called

```cpp
ostream &operator<<(ostream &out, const BTNode &node) {
    out << node.data << " ";
    if (node.left)  out << *(node.left);
    if (node.right) out << *(node.right);
    return out;
}
```

Note that we check if left and right are null after since references cannot be null.

When writing scripts:

1. Check for errors (arguments, etc.)
2. Do stuff (print helpful message if necessary)
3. Exit on error or exit with 0 on success

`$#` - num arguments

`$?` - exit code of last run program

`$@` - every argument

`f1 -ot f2` => file 1 older than file 2 
