# Lecture 7 - Oct. 6, 2015

## Basic I/O

In C++ there is an implicit conversion from cin (istream) to (void\*)

`cin` evaluates to `true` if `!cin.fail()`

`cin` evaluates to `true` if `cin.fail()`

We can use this fact to do things like:

```
int main() {
    int i;
    while (cin >> i) {
        count << i << endl;
    }
}
```

-

### Side note: bit shifting

In C: `21 >> 3;` shift 3 bits to the right;

`10101 (21) >> 3` -> `00010` (as if we pushed 3 bits off a "cliff")

This is the same in C++ if we use it on integers.

We use `cin >> x` where `>>` is an input operator. 

This is an example of operator overloading

-

Once a read fails, we must call `cin.clear()` to lower the fail flag, then `cin.ignore()` if we want to ignore that bad input.

```
#include <iostream>

int main() {
    int i;
    while(true) {
        if(cin >> i) { //read successful
            cout << i << endl;
            continue;
        }
        if(cin.eof()) { //EOF
            break;
        }
        //invalid input
        cin.clear();
        cin.ignore();
    }
}
```

Note that `cin` stops at the first occurrence of a whitespace character.

To get a full line, we can use `getline(cin, s)`

This reads into s from the first non whitespace character until `\n`.

You can use combinations of `cin` and `getline`.

### I/O Manipulators

To format output we can use I/O manipulators

`cout << hex` <-- changes the internal state of cout to print integers in hexadecimal

`cout << dec` <-- changes back to decimals

`noskipws` -- doesn't skip on whitespace

`boolalpha` -- prints `true/false` instead of `1/0`

Look up `<iomanip>` for others.

### Other Sources of Data

The stream abstraction can be applied to other sources of data.

e.g.) files

`#include <fstream>`

`ifstream` - read from a file

`ofstream` - write to a file

```
#include <iostream>
#include <fstream>

int main() {
    std::ifstream file("suite.txt");
    std::string s;
    while(file >> s) {
        std::cout << s << std::endl;
    }
}
```

**The file is closed when the stack frame of `main` is popped from memory.**

The default destructor of `file` is called.
