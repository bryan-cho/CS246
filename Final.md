#Final Review

## V-Table

See notes.

## Exceptions

```cpp
BinTree BinTree::operator=(const BinTree &other) {
    if (&other == this) { return *this; }
    delete left;
    delete right;
    data = other.data;
    left = other.left ? new BinTree(*other.left) : NULL;     <-- what happens if new throws an exception? 
    right = other.right ? new BinTree(*other.right) : NULL;     <-- what happens if new throws an exception? 
    return other;
}
```

**Stack unwinding** - when an exception is thrown, the exception will keep getting thrown down each successive stack frame until it is "caught". Whenever we "unwind" and leave a stack frame behind, the destructor of all stack allocated resources will be called for that stack frame.

#### RAII

**Resource Allocation is Initialization** - an idiom where we "indirectly" store all objects on the stack so our code is exception safe.

For instance, we can store a pointer to a dynamic array on a stack allocated object where the only purpose of its existence is to hold that pointer. This object will delete the pointer that it holds upon destruction.

There is a built in way to do this in C++03 and this is by using `auto_ptr<>`

#### Exception Safety Guarantees

**No-throw Guarantee**: The strongest guarantee. This basically guarantees that the code will never throw an exception.

**Strong Guarantee**: The code guarantees that it will either work as intended or throw an exception, but not both. i.e.) If an exception is thrown, nothing else will be done and the state of the program will remain unchanged.

**Basic Guarantee**: The code guarantees that the data still makes *sense* and is "safe". For instance, if adding an item to a LinkedList structure fails, the "size" field is unchanged.

**No Guarantee**: This code guarantees nothing. Any exceptional behavior is undefined.

We see that the above block of code has a **no guarantee** level of exception safety.

#### Making code exception safe

One way is to add a try-catch block with temporary pointers.

```cpp
BinTree BinTree::operator=(const BinTree &other) {
    if (&other == this) { return *this; }
    BinTree *temp1;        <-- this is new
    BinTree *temp2;        <-- this is new
    this->data = other.data;
    temp1 = other.left ? new BinTree(*other.left) : NULL;      
    try {
        temp2 = other.right ? new BinTree(*other.right) : NULL; 
    } catch (...) {
        delete temp1;
        throw;
    }
    delete left;
    delete right;
    this->left = temp1;
    this->right = temp2;
    return *this;
}
```
Another way is to do "copy & swap"

```cpp
void BinTree::swap(BinTree &other) {
    int tempData = other.data;
    BinTree *tempLeft = other.left;
    BinTree *tempRight = other.right;
    other.left = this->left;
    other.right = this->right;
    other.data = this->data;
    this->left = tempLeft;
    this->right = tempRight;
    this->data = tempData;
}

BinTree &operator=(const BinTree &other) {
    BinTree temp(other);
    this->swap(temp);
    return *this;
}
```

Both approaches will receive full marks on an exam.

## Mixed Assignment

Course notes are fine for this.

Know how this works and how to fix it.

## Casting

Course notes are fine for this too.

Know what to do with a bad cast.

## Final Exam Concepts (Post Midterm):

**Gotchas**:

* Derived class constructors call base class constructors

**Destructors (dtor)**

* Destructors are run when an object is destroyed
* Stack allocated objects are destroyed when they go out of scope
    * e.g.) Object is allocated inside the scope of a function and function returns
    * e.g.) Object is initialized in main and program terminates
* Derived class destructor calls base class destructor

**Stack allocated vs Heap allocated**

* When should we do this?
* Always allocate on stack unless:
    * value must outlive the scope
    * size of collection/array is unknown or subject to resizing
    * memory allocation is too big for the stack

**default dtor (free/built-in)**

* this calls the destructor on any fields that are objects

**When to implement custom dtor**

* we should implement a custom destructor when there are heap allocated fields that need to be deleted
    * this is only when the class has an "owns a" relationship with the field

**Separate compilation of classes**

* we split each 

**:: the scope resolution operator**

* need to use this when we are implementing methods
* this changes the scope to be local to the class we specify

**Assignment operator (operator=)**

* things to remember:
* can only be defined as a method
* other operators must be defined as a function
* right associated
* check for self-assignment as this should be valid
    * check if this is the same as the address of the other
* remember to make it exception safe
    * copy and swap idiom is useful for this
        * make temps, and swap
* fundamentally different from copy constructor
* copy constructor makes an entirely new object
* assignment operator makes changes to an existing object

**Signature of operator=**
    
* returns a reference (this is so we can make it associative)
* can either pass by reference or by value
* remember to make a copy if taken by reference
* implemented as a method

**default operator= (shallow assignment)**
    
* default assignment operator basically copies all fields
* pointers will be copied to have the same address
* this is called a shallow copy

**When to write custom operator=**
    
* we need to do this whenever we require deep copy
* we also need this whenever we need have derived classes that have problems with assignment (mixed assignment/partial assignment)

**self assignment check**

* this was covered above

**Assignment operator using copy and swap**

* covered above

**Rule of 3**

If you need to write a custom: 
* copy constructor
* destructor
* operator=

Usually need to implement all three.

**Member functions vs Standalone functions**

* Member functions or methods have an implicit `this` pointer
* Methods can be encapsulated (security)
* Standalone functions do not have the above

**Arrays of Objects** 

* we can have arrays of objects
* pointers or objects are fine
* when the array is initialized, the default constructor will run (or no parameter constructor) for each object

**const Methods**

* const methods cannot make any changes to the fields of the object
* unless the fields are `mutable`

**mutable keyword**

* mentioend above

**static keyword in C++**

* common among all instances of a class
* associates the field with the class and not objects of the class
* static fields must be defined external to the type's definition
* `int Student::numObjects = 0;`
* We cannot do this in the constructor because the constructor is used for every object that is created
* static methods do not have access to the `this` pointer
* do not need an object to call a function inside a class that is static
* **derived classes have access to base class static members**

**Singleton Pattern**

* Create only one object of this kind
* Wallet - singleton
* Expense - all have access to wallet

**atexit function from cstdlib**

* takes a pointer to a function as an argument
* runs on exit
* **must take 0 parameters, and must be a void function**
* multiple calls to atexit will **stack** up
* will have LIFO behaviour

**Encapsulation**

* public/private/protected/mutable/const
* flexibility to change implementation
* information hiding
* maintain class invariants (things that don't change)

**Difference between struct and class keyword**

* struct is all public by default
* class is all private by default

**accessor/mutator methods**

* getters and setters
* remember to make getters to be const

**friend keyword**

* class with private fields and no accessors can have "friends"
* useful for operators
* `friend std::ostream& operator<<(...);`

**System Modelling (UML)**

* identifying the abstractions (classes)
* relationship between those classes
* UML: Unified Modeling Language
* **Class**
    * box with 3 sections
    * class name (italics if abstract)
    * other 2 are optional
    * second section is for fields
    * third section is for methods
    * public: +
    * private: -
    * protected: #

**Relationship 1: Composition**

* embed an object within another object
* "owns a" relationship
* arrow with **black** filled diamond (object that owns)
* arrow with **black** filled arrowhead (object that is owned)
* A "owns a" B if:    
    * If B cannot exist 
    * If B gets destroyed when A gets destroyed
    * If A gets copied, B gets copied
        * copying != sharing
* example: car "owns" four wheels.
* destroying car implies destroying wheels
* copying car implies copying wheels (not shared!)


**Relationshop 2: Aggregation**

* arrow with **white** diamond (object that has)
* arrow with **black** filled arrowhead (object that is "had")
* "has a" relationship
* think of a catalogue that "aggregates" a bunch of car parts and displays them
* the car parts can exist separately from the catalogue
* A "has a" B if:
    * B has an existence apart from its association with A
    * A is destroyed, then B lives on
    * A is copied, B is not (shallow copy). Copies of A share same B

**Relationship 3: Inheritance**

* To model relationships between classes, we use inheritance
* For instance, suppose we want to have a bunch of classes for to keep track of computer models
* We could create a bunch of classes:
    * Computer, for a general computer
    * Desktop, for a desktop computer
    * Laptop, for a laptop computer
    * Tablet, for a tablet computer
* This does not capture the relationship between the different classes
* To solve this, we use **inheritance**

**Base Class**

* In our example, Computer can be the base class or the *super class*
* This class will have all of the features that are common among all types of computers

**Derived Class**

* Laptop, Desktop, Tablet
* Each are still *Computers*
* Each have their own unique set of features that differentiate it from a general Computer
* Derived classes **inherit** fields and methods from the base class
    * Everything is inherited!
    * In memory, the super class literally sits on top of the derived class and so everything from the base class is essentially inherited by the derived class
* Subclasses cannot access private members but **DO** exist


- 4 steps to object creation
- protected visibility
- Virtual keyword (isItHeavy example) 
- Polymorphism 
- Virtual Destructor: why and when
- make (covered in tutorial): only basic understanding needed of what it does
- Pure Virtual Methods
- Abstract vs Concrete Classes
- Observer Pattern
- Decorator Pattern
- Factory Method Pattern
- Template Method Pattern
- Template classes
- STL: vector/iterators
- STL map
- Visitor Design Pattern
- Double Dispatch
- Adding functionality without changing class hierarchy code
- Circular Dependencies: solution: forward declare when possible
- Compilation Dependencies: when to forward declare vs when to include
- pImpl Idiom
- Generalize the pImpl Idiom: Bridge Design Pattern
- Revisiting the big three (inheritance)
- Partial Assignment problem
- Mixed Assignment problem
- Solution without making operator= virtual
- Casting: 4 kinds of casts
- Exceptions
- Exceptional Control Flow 
- Stack unwinding
- Solution to mixed/partial assignment problem with virtual operator=
- Three levels of exception safety
- `auto_ptr`
- VTable and Vptr
- superficial knowledge of Return Value Optimization (RVO)


