# Lecture 12 - Oct. 22, 2015

Closing remarks on separate compilation, Intro to C++ Classes

Some precautions:

* Never include .cc files
* Never compile .h files
* Never use `using namespace std` in .h files

## C++ Classes

**OOP**: we can put functions inside a struct. 

**Class**: a *struct* that can contain member functions.

**Object**: an *instance* of a class. 

**Member function/Method**: function inside of a class.

* You call methods on objects.
* Methods have access to all of the fields of the object on which the method was called
* Has a hidden parameter called, "this"
* "this" is a pointer to the object on which the method was called

### Initiating Objects

C++ allows writing methods to construct objects, called **constructors**.

There is a default constructor with every class.

If you want to define your own constructor you can override it by defining a method using the same name as the class.

```cpp
class Student{
    public:
        Student(string name, int grade) {
            this->name = name;
            this->grade = grade;
        }
    private:
        string name;
        int grade;
};
```

We can define default arguments:

```cpp
class Student{
    public:
        Student(string name="bob", int grade=0) {
            this->name = name;
            this->grade = grade;
        }
    private:
        string name;
        int grade;
};
```

Better practice is to define both the default constructor using default values, and an overloaded constructor. Both will use the **initializer list**:

```cpp
class Student{
    public: 
        Student()                       : name("bob"),  grade(0)        { }
        Student(string name, int grade) : name(name),   grade(grade)    { }
    private:
        string name;
        int grade;
};
```

However, this is rather tedious as we would have to define 4 different functions to handle the different cases of initialization. 

For example, the above definition cannot handle this: `Student bob("bob"); bob.grade = 0???`

Using default arguments should be fine for most cases, but the last example is good for readability and is cleaner.

We can initialize objects in various ways:

```cpp
Student alice;                            // Stack allocated; C-style initialization (struct)
Student alice = {"alice", 0};             // Stack allocated; C-style initialization (struct)
Student alice = Student();                // Value initialization (assuming default constructor still exists)
Student alice = Student(//arguments);     // Stack allocated 
Student alice(//arguments);               // Stack allocated
Student alice = new Student(//arguments); // Heap allocated
```

Some notes:

1. Every class comes with a default constructor (0 parameter)
    * This calls the default constructor on fields that are objects
    * If you write any constructor, the **default constructor is gone**
    * If you write any constructor, you cannot use C-style initialization.

Example:

```cpp
struct A {
    int x;
    Student s;
    Student *p;
};

A myA;
```

When `myA` is instantiated, it will call the default constructor for `Student s`;

*Primitive types* and *pointers* are uninitialized by the default constructor when you do not use *value initialization*.

**Value initialization**: initializing an object by explicitly calling the constructor.

It is recommended to use C-style initialization if you want to initialize an "empty" object.

```cpp
Student alice = Student();
```

Note that *field initializers* are not allowed in C++03.

For example, suppose we have a struct definition that needs to keep a constant or a reference. These need to be initialized.

```cpp
struct Student {
    const int myconst = 10; // INVALID
    int &myref = __;        // INVALID
};
```

In order to understand how we might solve this problem, we need to look into what happens when an object is created.

When an object is created:

1. Space is allocated (stack/heap)
2. Field initialization; default constructor for fields that are objects are called
3. Constructor body runs

We see that step 3 is too late for us to use the constructor body to initialize constants and references.

We must "hijack" step 2.

New syntax: Member initialization list (MIL). This was shown above.

```cpp
class Student {
    private:
        const int myconst;
        int &myref;
    public:
        Student(int id, int &r): myconst(id),   myref(r)    { }
};
```

You can use this for any member variable.

If a MIL does not initialize a field that is an object, the default constructor for step 2 will still run.

Fields are initialized in declaration order, irrespective of the order in MIL.  

In other words, if field a comes before b, we must initialize a then b in the list, or we will get a compiler warning.
