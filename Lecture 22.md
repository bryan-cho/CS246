# Lecture 22 - Nov. 26, 2015

Big Three, Casting

## Big Three (continued)

Last time we went over problems that may arise with the assignment operator when mixed with inheritance.

```cpp
Book *bp1 = new TextBook(---);
Book *bp2 = new TextBook(---);
*bp1 = *bp2;
```

The assignment above calls `Book`'s assignment operator. This does not copy over the `TextBook` part of the object. This is called **partial assignment**.

Can we make the assignment operator virtual?

```cpp
class Book {
    public:
        virtual Book& operator=(const Book &); //dynamic dispatch
};

class TextBook : public Book {
    TextBook& operator=() // <-- What type should this take?
};
```

We can only override methods by taking in the **same type**. However, this introduces another problem. 

```cpp
class TextBook : public Book {
    TextBook& operator=(const Book&);
};
```

So now we override the operator by taking in a `Book` reference. But this lets us call `TextBook`'s assignment operator with any `Book` object! That doesn't make any sense because calling `TextBook::operator=` with a `Comic` for instance should not be valid.

How do we fix this?

Recommendation: Always make the base class of a hierarchy **abstract**.

Then, we can make the assignment operator of the base class to be *protected*. All sub classes of this base class will have access to this assignment operator.

```cpp
class AbstractBook {
    private:
        string title, author;
        int numPages;
    protected:
        AbstractBook& operator=(const AbstractBook&);
};

class NormalBook : public AbstractBook {
    public:
        NormalBook& operator=(const NormalBook& other) {
            AbstractBook::operator=(other); // NormalBook "is a" AbstractBook
            return *this;
        }
};

AbstractBook *abp1 = new NormalBook(---);
AbstractBook *abp2 = new NormalBook(---);
*abp1 = *abp2; // won't compile
```

We are trying to do assignment through `AbstractBook` pointers. However, `AbstractBook` does not have access to the protected assignment operator.

## Casting

*In C*:

```c
Node n;
int *p = (int *) &n;
```

This is C-style casting.

In C++, there are 4 types of casting. The idea is that the most appropriate one should be used since the single C-style cast was too powerful. Another reason was that the casting using parentheses `()` was hard to find in code as parentheses are used for many other purposes.

*In C++*:

There are 4 different types of casting:

1. `static_cast`
2. `const_cast`
3. `reinterpret_cast`
4. `dynamic_cast`

**static_cast**: Converting a pointer of a base class to a pointer of a derived class, convert numeric data types such as enums to ints or ints to floats. Not necessarily safe as no run-time type checks are done. 

```cpp
int m = 9;
int n = 2;
cout << m/n; // prints 4
cout << static_cast<double>(m)/n; // prints 4.5
```

Syntax: `static_cast<//desired type>(input)`

```cpp
Book *bp = ---;
Textbook *bp = static_cast<TextBook*>(bp);
```

We can do this as long as we know **for sure** that `bp` was pointing to a `TextBook` object. If it was not pointing to a `TextBook` object, the behavior is undefined.

Say for instance, `bp` was pointing to a `Comic` object. Then calling `bp->getTopic()` is completely undefined. For instance, `getTopic()` instructs to return the value at the fourth field of the object. So `Comic` may return the `protagonist`. What if `bp` is a `NormalBook`? We may get a seg fault as `NormalBook`s do not have a fourth field. We may get some garbage value. Again, the behaviour is **undefined**.

`static_cast` is an **unchecked cast**.

**const_cast**: Convert a const variable to a mutable variable. 

```cpp
void library(int *p);
void myCode(const int *q) {
    library(q); // will not compile
}

library(const_cast<int*>(q)); // will compile
```

We can use `const_cast` to remove the `const` property of `q`. This may be useful if we want to use a library function that is not necessarily `const` but we know it will not change the value of the pointer.

If `library()` does change the value of `*p`, the behaviour is undefined.

**reinterpret_cast**: It is purely a compiler directive which instructs the compiler to treat the sequence of bits (object representation) of expression as if it had the `new_type`.

```cpp
Vec v; // 3d vector
Student *sp = reinterpret_cast<Student*>(&v);
sp->grade(); // will compile
```

The behaviour of the above program is completely dependent on how objects are represented in memory by the compiler.

Recall that what grade does is `0.4*(1st field) + 0.2*(2nd field) + 0.4*(3rd field)`;

So if `v` is represented in memory as three contiguous fields, then we would get: `0.4*x + 0.2*y + 0.4*z`;

This means we could potentially bypass the encapsulation of any class.

**dynamic_cast**: If the cast is successful, `dynamic_cast` returns a value of type `new_type`. If the cast fails and `new_type` is a pointer type, it returns a null pointer of that type. 

```cpp
Book *collection[100];
for(---) {
    Book *bp = collection[i];
    TextBook *tbp = dynamic_cast<TextBook*>(bp);
    if (tbp != NULL) {
        cout << tbp->getTopic();
    } else {
        cout << "Not a TextBook";
    }
}
```

To use `dynamic_cast` the hierarchy must have at least one virtual method.

**RTTI (Runtime Type Information)**:

```cpp
void whatIsIt(Book *bp) {
    if (dynamic_cast<TextBook*>(bp)) {
        cout << "TextBook";
    } else if (dynamic_cast<Comic*>(bp)) {
        cout << "Comic";
    } else {
        cout << "Book";
    }
}
```

This code is *highly coupled* to the `Book` hierarchy. We would need to update this each time we update the hierarchy.
