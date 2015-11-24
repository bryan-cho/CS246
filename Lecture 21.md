# Lecture 21 - Nov. 24, 2015

Compilation Dependencies, Pointer to Implementation, "Big Three"

## Compilation Dependencies

Forward declare or include?

Benefits of forward declarations:

* Avoids circular dependencies
* Reduces compilation times

We should use forward declarations whenever we can.

So when can we forward declare over including?

```cpp
// In a.h
class A { --- };

// In b.h
#include "a.h"
class B : public A {

};
```

Needs to know what the fields of A are, when a B object is being created.

Hence we must `include`

```cpp
// in a.h
class A { --- };

// in c.h
#include "a.h"
class C {
    A myA;
};

// in d.h
class A;
class D {
    A *myA;
}
```

Class C needs to know the size of A, and to know the size of A, it needs to know the fields of A.

We must also `include` in this case.

Class D however, does not need to know the size of A. The size of pointers are not dependent on the type.

We can forward declare `class A`.

```cpp
// in d.cc
#include "d.h"
#include "a.h"
void D::foo() {
    A myA;
    myA->print();
}
```

In this case, the implementation needs to know if `A` has a `print` method. 

Here, we must `include`.

```cpp
// in e.h
class A;
class E {
    A foo(A a);
};
```

`foo` is a method, and we are only defining the prototype.  This does not depend on the size of A.

If we were to implement `foo` we would need to include the header for `A`.

**NOTE**: We may see a question on the exam with code that asks us whether an `include` is necessary or whether we can get away with a forward declaration.

## Pointer to Implementation

Suppose we had the following:

```cpp
// in window.h
class XWindow {
    Display *d;
    GC gc;
    public:
        void drawRectangle();
};

// in client.cc
#include "window.h"
// use public interface to XWindow
```

With this, **ANY** change to `window.h` (even to private fields), requires recompiling `client.cc`.

We can get around this by *replacing* the private implementation with a **pointer to the impementation**.

```cpp
// in windowimpl.h
struct XWindowImpl {
    Display *d;
    GC gc;
};

// in window.h
struct XWindowImpl;
class XWindow {
    XWindowImpl *pImpl;
    public:
        void drawRectangle();
};
```

Notice `XWindowImpl` is a struct and all members are public by default. This is because the only way we can access the members of `XWindowImpl` is through a private pointer in `XWindow`.

Now, the only compilation dependency that exists for any change to private members of `XWindow` exists only in `window.cc`.

```cpp
// in window.cc
#include "window.h"
void XWindow::drawRectangle() {
    this->pImpl->d->update();
}
```

Now, `client.cc` above would not have to recompile if we make any changes to the private members of `XWindow`.

**Low coupling**:

* code to a public interface
* no friends
* no public fields

**High cohesion**:

* interaction to work towards the same goal
* MVC

## Big Three (With Inheritance)

**Destructor**:

* base class destructor should be virtual
* subclass destructor automatically calls base class destructor

**Copy Constructor**:

* Note that by default, the default copy constructor for the super class will be called and then the default copy constructor will be called for the subclass

```cpp
Textbook b1;
Textbook b2 = b1; // copy constructor
Textbook b2(b1); // equivalent as above

//Note assignment looks like this
Textbook b2;
b2 = b1;

TextBook::TextBook(const TextBook &other)
: Book(other)
, topic(other.topic) {}

Book::Book(const Book &other)
: title(other.title)
, author(other.author)
, numPages(other.numPages);
```

What we are doing here is that the subclass, `Textbook` is first calling the copy constructor of the superclass, `Book`, then it is copying the fields of `other`.

Note that the private fields are accessible because private fields of the same class can be accessed.

**Assignment Operator**: 

* By default, the default assignment operator of the super class will be called then the assignment operator of the subclass will be called.

```cpp
TextBook &TextBook::operator=(const TextBook &other) {
    Book::operator=(other);
    topic = other.topic;
    return *this;
}
```

The only added complexity is that we must deal with the superclass first and then the subclass.

All other checks that need to be made for the assignment operator still apply.

What if we have a "is-a" relationship?

```cpp
Book *pb1 = new TextBook("CS246", "Nomair", 200, "C++");
Book *pb2 = new TextBook("CS136", "Adam", 100, "C");

*pb1 = *pb2; //assignment operator, but through Book pointers, not TextBook pointers
```

This will not properly copy over the `TextBook` part of `pb2`, since only the `Book` assignment operator is called as the assignment operator is not virtual by default.

Printing the contents of `*pb1` will give: "CS136", "Adam", 100, "C++" <-- not from `*pb2`


