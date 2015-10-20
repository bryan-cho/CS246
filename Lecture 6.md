# Lecture 6

## Testing, C++, Intro to I/O

When writing tests for our assignments, come up with test cases and then run the *buggy* programs with these test cases using our custom input and expected output.

Our testing program should be able to catch the bugs in each program as long as we write tests that test all parts of the code.

Try:

* Bad inputs:
    * Edge cases - boundaries
    * Corner cases - where two boundaries meet
    * In the case of numbers: negative, 0, positive

### History of C++

Invented by Bjarne Stroustrup, used to work at AT&T Labs
Unix and C were developed in AT&T Labs

Simula67 <-- First OOP language
Bjarne was experimenting with Simula67, and wanted that to be in C.
This led to a language called **C with Classes**

Nice thing about this was that *C with Classes* was just C with additional features. Existing C programmers could adapt easily.

We will use C++03 in this course.

### Streams

C++ provides us with three stream "variables"

**cout** - used to send data to stdout
**cin** - used to get data from stdin
**cerr** - used to send data to stderr

**<<** - output operator "put to"
**>>** - input operator "get from"

If one input fails, all inputs fail.

If a read fails, `cin.fail() == true`.
If a read fails because of an EOF, `cin.fail() == true && cin.eof() == true`

