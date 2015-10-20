# Lecture 8 - Oct. 8, 2015

## More I/O

We can use a variable of type `ofstream` just like `cout`.

```cpp
ofstream file("suite.txt");
string s;
while(cin >> s) {
    file << s;
}
```

### Introduction to String Stream

Can attach a stream to a string to read/write.

`#include <sstream>`

We get access to:

`istringstream`

`ostringstream`

This takes input and "builds" a string by concatenating.

```cpp
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main () {
  ostringstream ss;
  int lo = 1, hi = 100;
  ss << "Enter a # between " << lo << " and " << hi;
  string s = ss.str();
  cout << s << endl;
}
```

Useful for converting a string to an int.

```cpp
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main () {
  int n;
  while (true) {
    cout << "Enter a number:" << endl;
    string s;
    //read the number as a string, break if EOF or read fails
    if (!(cin >> s)) break;

    //initialize an input string stream from the string
    istringstream ss(s);

    //try to read an int from this istringstream
    //Question: in which scenario does this read fail?
    if (ss >> n) break;
    
    cout << "That was not a number!" << endl;
  }
  cout << "You entered " << n << endl;
}
//Question: What happens when a read into a string fails?
```

Read from `stdin` and print if number

```cpp
#include <iostream>
#include <sstream>
using namespace std;

int main () {
  string s;
  while (cin >> s) {
    istringstream ss(s);
    int n; 
    if (ss >> n) cout << n << endl;
  }
}
```

## The String Type

C-style strings are null-terminated char arrays.

* Memory management was done manually
* Null terminating can cause problems

C++ has a type `string` that will abstract away the processes that are required for managing C-style strings.

* Automatic memory management
* No null terminator

`string s = "hello";`

Notice that `string s` is the C++ string type and `"hello";` is a C-style string `(char *)`.

### String Operations

**Equality** 

`s1 == s2;`

Same applies for `!=, <, >, <=, >=`

**Concatenation**

`s1 + s2;` returns new string

### Default Arguments

We will refactor this code to have a function that prints the contents of a file instead.

```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main () {
  ifstream file("suite.txt");
  string s;
  while (file >> s) {
    cout << s << endl;
  }
}
```

```cpp
void print(string filename) {
    ifstream file(filename) <-- this will not compile
}
```

The code above will not compile since ifstream(file) expects a C-style string.

We must make the following change:

```cpp
void print(string filename) {
    ifstream file(filename.c_str());
}
```

Now we introduce the concept of default arguments.

```cpp
void print(string filename = "default.txt") {
    ...
}
```

This will refer to `default.txt` if no arguments are given.

It will take in an argument if provided.

**NOTE:** A parameter with a default value can only be followed by parameters with default values.

e.g.)

Valid:

`void print(string filename = "default.txt", int length = 5)`

The above is equivalent to defining

```cpp
void print();
void print(string filename);
void print(string filename, int length);
```

`void print(string filename, int length = 5)`

Invalid:

`void print(string filename = "default.txt", int length)`

With the above valid print functions, this is also invalid:

`print(5)` OR `print(,5)` <-- this will **not** call `print` with the default value 

## Function Overloading

Functions in C++ can have the same name as long as they differ in:

* Number of parameters
* Types of parameters

Example:

```cpp
int negate(int a) { return -1 * a; }
bool negate(bool a) { return !a; }
```

**NOTE:** Cannot overload a function just by changing return types (might work but shouldn't do it)

We have seen this from the following:

```cpp
21 >> 3;   // bit shifting
cin >> n;  // input operator
```

Note that an alternate form of `>>` is 

```cpp
operator>>(21, 3)
operator>>(cin, n)
```

We can see that this is a form of "function overloading"

## Declarations

Functions must be declared before they are used.

You should know about forward declarations, etc.

Check out `function/forwardBad.cc` and `function/forwardGood.cc` in lecture examples.
