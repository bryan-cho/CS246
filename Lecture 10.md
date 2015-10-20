# Lecture 10 - Oct. 15, 2015

Dynamic Memory, Operators, Preprocessor

`valgrind` - suite of tools for debugging and profiling programs

## Operator overloading

If our operator doesn't need to change the value of the original input it is good practice to make the reference `const`. This also has other good effects. 

Obviously, if the operator needs to make changes to what is being passed in, we need to pass in a reference.

Important note about operator overloading:

When overloading operators, we must put `const` for our references to allow **cascading**.

If we do not place `const`, then we are not allowed to do expressions like this:

```cpp
someType x;
someType y;

someType z = x + y + x;
```

This is because `someType::operator+` returns a temporary *rvalue* of type `someType`;

It is not an *lvalue* until that temporary *rvalue* is assigned to a variable. 

Recall that in C++ we cannot bind a reference to an *rvalue*. 

If that was possible, we could do things like this:

```cpp
COMPLEX& c = a + b; //What exactly are we referencing?
c = 137;            //What did we just change?
```

Hence, by changing the overloaded operator to take a `const` reference, we can cascade our operators. This is because in C++ you can bind `const` references to *rvalues*.

**NOTE:** If we want to define operators that take for instance an `(int, someType)` we can easily define the converse `(someType, int)` by having the second one call the first one.

### Overloading Output Operator

Suppose we have:

```cpp
struct Grade {
    string name;
    string grade;
};
```

We can do the following:

```cpp
ostream &operator<< (ostream &out, const Grade &g) {
    out << "Student:" << g.name << " ";
    out << g.grade << "%";
    return out;
}
```

so that we can easily output student grades.

### Overloading Input Operator

For input operators, we should not take in a `const` reference.

```cpp
istream &operator>> (istream &in, Grade &g) { // Note: Grade is not const in this one
    in >> g.name >> g.grade;
    if (g.grade < 0) g.grade = 0;
    if (g.grade > 100) g.grade = 100;
    return in;
}
```

Notice that we put restrictions straight into the definition of the operator.

Now we don't have to worry about it when we use these operators.

## C++ Preprocessor

Source Code --> [Preprocessor] --> [Compiler] --> 

`#` --> preprocessor directive.

`#include <____>` will "copy & paste"

`#include "____.h"` will use the file in the current directory

The compiler can take certain flags:

`-E` - stop after running preprocessor

`-P` - no line numbers

Other preprocessor directives:

`#define VAR VALUE` - search & replace VAR with VALUE  
