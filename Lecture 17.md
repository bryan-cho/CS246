# Lecture 17 - Nov. 10, 2015

Missed last lecture... 

Apparently they went over:

System modelling

* composition, aggregation, inheritance
* `Private` really means private
* `Protected` keyword
    * Visible to that class or any of its subclasses

```cpp
class Book {
    protected:
        string author;
}

class TextBook : public Book {
    public:
        void addAuthor(string auth) {
            this->author += auth;    
        }
}
```

If the `author` field was private, we would not be able to do the above.

The following is still invalid!

```cpp
TextBook tb();
tb.author = "___";
```

`author` is protected.

General rule:

* Keep fields private
* Provide **protected** methods (accessors/mutators)

**UML**:

* Private: `-`
* Protected: `#`
* Public: `+`

Suppose Book has a public `isItHeavy` method.

```cpp
class Book {
    private:
        int numPages;
    protected:
        int getNumPages() { return this->numPages; }
    public:
        bool isItHeavy() { return this->numPages > 200; }
}
```

What if we want to have a different definition of `isItHeavy` for a TextBook class or a Comic class?

We can **override** the inherited `isItHeavy` method.

```cpp
class TextBook : public Book {
    public:
        bool isItHeavy() { return getNumPages() > 400; }
}

class Comic : public Comic {
    public:
        bool isItHeavy() { return getNumPages() > 30; }
}
```

**Note**: notice the use of `getNumPages()` instead of `this->numPages`. This is because `numPages` is `private` and can only be accessed by either `protected` or `public` methods.

Now we can do this:

```cpp
Book b(50);
Comic c(50);

std::cout << std::boolalpha << b.isItHeavy() << std::endl;
std::cout << std::boolalpha << b.isItHeavy() << std::endl;

>> false
>> true
```

### Slicing

Suppose we did the following:

```cpp
Book b2 = Comic(50);

b2.isItHeavy() // Book::isItHeavy
```

It is valid for us to declare a `Comic` object as a `Book` object.

This is because in memory, a `Comic` object is actually a `Book` object and a `Comic` object in a contiguous set of memory.

When we do

```cpp
Book b2 = Comic(50);
```

We are **slicing** away the `Comic` part of the object.

Thus, the call to `isItHeavy` will call Book's `isItHeavy`.

To prevent slicing we can declare the object as a pointer!

**FINAL MATERIAL**

```cpp
Book *bp = new Comic(50);
Comic *cp = new Comic(50);

bp->isItHeavy() // Book::isItHeavy
cp->isItHeavy() // Comic::isItHeavy
```

However, we still see that calling `isItHeavy` with a Book pointer still invokes the `Book::isItHeavy` method!

This is because the **compiler decides which method to call based on the declared type of the variable** (static dispatch).

**Static** meaning that it was decided upon compilation.

To mitigate this issue, we now examine the concept of **virtual methods**.

## Virtual Methods

What is the problem?

The default behaviour of the compiler is to look at the declared type of the variable.

Instead of this, we want to be able to invoke methods that pertain to the actual type of the object. 

**Virtual Method**: choose which method to run based on the runtime type of the object. (dynamic dispatch)

Now we can do things like this:

```cpp
Book *collection[100];

for (int i=0; i<100; i++) {
    collection[i]->isItHeavy();
}
```

Depending on what type the book is, the correct `isItHeavy` will be called.

This is the essence of **polymorphism**.

**Polymorphism**: ability to accomodate multiple types in a single abstraction.

We have already seen this.

```cpp
ostream& operator<<(ostream &out, ---);

cout << g;
ofstream f(---);
f << g;
```

This is possible because:

`ofstream` **is a** `ostream` object.

## Virtual Destructors

Before we move on to virtual destructors we establish one thing.

**Rule**: When a subclass destructor is called, it will call the base class' destructor as well.

Similar to virtual methods, we want to use virtual destructors so that when a inheriting object is destroyed, it calls the correct destructor.

```cpp

class X {
    int *x;
    public:
        X (int n) : x(new int[n]) {}
        virtual ~X() { delete[] x; }
};

class Y : public X {
    int *y;
    public:
        Y (int n) : y(new int[n]) {}
        ~Y () { delete[] y; }
}

X *xp = new Y(5);
delete xp;
```

The above will not memory leak since it will first call Y's destructor, then X's destructor.

**Note**:

In UML: virtual is italics (i.e) the function name is in italics)

## Pure Virtual/abstract/concrete

Suppose we have the following classes:

```cpp
class Student {
    public:
        int numCourses;
    protected:
        int numCourses() { return this->numCourses; }
}

class Regular : public Student {
    public:
        int fees() {}
}

class Coop : public Student {
    public:
        int fees() {}
}
```

We see that Regular and Coop are classes that inherit from Student.

However, we see that there really is no Student that is not a Regular student or a Coop student.

`fees` is undefined for Student. We do not want an implementation for it.

We make the method **pure virtual**.

We do this like so:

```cpp
class Student {
    public:
        virtual int fees() = 0;
}
```

Pure virtual methods have no implementations.

**Abstract**: classes that contain at least one pure virtual method is considered **abstract**.

We cannot create objects of abstract classes.

(This is as expected since what happens with a Student object that invokes `fees()`? It is undefined behaviour)

**Note**:

In UML: abstract classes are in italics (i.e.) the class name is in italics)

A derived class **inherits all pure virtual methods**.

This would make the derived class also abstract unless **all pure virtual** methods are implemented.

**Concrete**: a class which contains no pure virtual methods is called **concrete**.
