# Lecture 15 - Nov. 3, 2015

const, static, Singleton Design Pattern, Encapsulation

### const

```cpp
struct Student {
    int assignments, midterm, final;
    float grade() {
        return (assignments * 0.4) + (midterm * 0.2) + (final * 0.4);
    }
}

const Student billy (60, 70, 80);
billy.grade();                      <-- compile time error
```

`const` objects can only call `const` methods.

`const` methods do not change the fields of the object.

What if we want to have a member variable that *can* be mutated by a `const` objects?

```cpp
struct Student {
    int assignments, midterm, final;
    mutable int numCalls;
    float grade() const{
        numCalls++
        return (assigments * 0.4) + (midterm * 0.2) + (final * 0.4);
    }
}
```

Notice the keyword `mutable`.

This allows a `const` method to mutate that specific member variable.

### static

**Static fields**: associates the field with the class and not objects of the class.

Essentially, this will be *shared* among all instances of that class.

```cpp
struct Student {
    static int numStudents;
    Student() { numStudents++ }
}
```

Static fields must be defined external to the type's definition.

In student.cc:

```cpp
int Student::numObjects = 0;
```

### static Member Functions

We do not need an object to call a function inside a class that is static.

static member functions do not have access to the `this` pointer.

**Note**: A static member function can only call other static member functions and access static fields.

From previous example:

```cpp
static void printNumObjects() {
    std::cout << numObjects << std::endl;
}
```

## Design Patterns

If you have "this" kind of problem, then "this" technique might be useful.

### Singleton Pattern

We have a class C, and we want our program to create only one objct of this kind.

e.g.) Finances

Wallet - only one, a singleton

Expense - all have access to wallet

See examples in the course notes.

Under `<cstlib>` there is a `atexit` function that takes a pointer to a function as an argument

Notes: 

* Must be a 0 parameter, void return type function

Will run the registered function at exit.

Multiple calls to atexit will **stack** up. 

LIFO behaviour.

The singleton example breaks as soon as someone else uses the wallet constructor.

## Encapsulation

* treat objects as black boxes (capsules)
* hide implementation

Clients access funcitonality using an exposed interface.

```cpp
struct Vec {
    Vec(int x, int y) ----
    private:
        int x,y;
    public:
        Vec operator+(const Vec &v1) {
            Vec v(x + v1.x, y + v1.y);
            return v;
        }
}
```

Private members can only be accessed by methods of the same class (not really).

Advice: all fields (member variables) should be private.

`struct`s by default have public visibility on all members.

The `class` keyword defines classes with members that are **private** by default.

```cpp
class Vec {
    int x, y;
    public:
        Vec() {---}
        Vec operator+() {---}
}
```

Why make fields private?

* maintain class invariants e.g.) keep x,y positive
* flexibility to change implementation e.g.) switching to polar coordinates
* we can still easily provide accessors/mutators
    * getters/setters

 
