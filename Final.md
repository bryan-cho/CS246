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

When an object is constructed:

1. Space is allocated
2. Default constructors are called for all fields in declaration order
3. Constructor body runs

When an object is destroyed:

1. Destructor body runs
2. Destructors are invoked for all fields in reverse order
3. Space is deallocated

Basically the reverse of an object construction.

For derived classes, the story is slightly different:

When a derived class object is constructed:

1. Space is allocated
2. Super class is constructed
3. Default constructors are called for all fields in declaration order
4. Constructor body runs

When a derived class object is destroyed:

1. Destructor body runs
2. Destructors are invoked for all fields in reverse order
3. Destructor for super class is invoked
4. Space is deallocated


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
* static pointer to an instance
* static getInstance function
* Private constructor
* Public getter for the only instance
    * Within the getInstance, it creates the instance if it doesn't exist
    * We check if the instance is NULL and create it if it is NULL
    * Return the new instance
    * Otherwise, we just return the existing instance
* Each `Expense` constructor sets the wallet to be `Wallet::getInstance()`
* Delete it atexit

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
* "is a" relationship
* A "is a" B if B inherits from A

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
* **NOTE** We cannot initialize the private members of the field in the derived class constructor!

**4 steps to object creation**

* See above

**protected visibility**

* To mitigate the issue of derived classes not having access to the base class members, we can have *protected* visibility for members
* `protected` members give full access to derived classes
* Good style is to provide `protected` accessors/mutators instead of giving direct access to members 

**Virtual keyword (isItHeavy example)** 

* This is an extended example but worth going through

We can have many cases:

```cpp
#include <iostream>
class Book {
    public:
        void sayHello() {
            std::cout << "Hi I'm a book" << std::endl;
        }
};

class TextBook : public Book {
    public:
        void sayHello() {
            std::cout << "Hi I'm a textbook" << std::endl;
        }
};
```

Suppose we have the above set up.

Here are the different cases that can arise:

```cpp
void sayHelloTB(TextBook& t) {
    t.sayHello();
}

void sayHello(Book& b) {
    b.sayHello();
}

int main() {
    Book b;
    b.sayHello(); // prints "Hi I'm a book"
    TextBook t;
    t.sayHello(); // prints "Hi I'm a textbook"
    sayHello(t); // prints "Hi I'm a book"
    sayHelloTB(t); // prints "Hi I'm a textbook"   
    Book* pb = new TextBook();
    pb->sayHello(); // prints "Hi I'm a book"
}
```

Now, we try the same example but with a different set up:

```cpp
#include <iostream>
class Book {
    public:
        virtual void sayHello() {
            std::cout << "Hi I'm a book" << std::endl;
        }
};
```

Now, the above main function prints the following:

```
Hi I'm a book
Hi I'm a textbook
Hi I'm a textbook
Hi I'm a textbook
Hi I'm a textbook
```

Notice the difference? Even if the function expects a `Book` reference, the `virtual` keyword makes sure that the correct function is called based on the run time type of `b`.

Check the example in the `exam` folder.

**Polymorphism**

* Multiple definitions
    * "The ability to accommodate multiple types in a single abstraction (class)
    * "Call to a method will cause a different function to be executed depending on the type of the object at *run time*
    * Overloading, overriding, virtual methods, etc. 

**Virtual Destructor: why and when**

* Recall: when a subclass destructor is called, it will call the base class' destructor as well
* We want to use virtual destructors so that when an inheriting object is destroyed, it calls the correct destructor
* Since if the derived class destructor gets called, the base class destructor gets called, we need not worry about calling the base class destructor
* Use this when you are using **base class pointers to point at many different types of derived classes**
* This is also important if any derived object is "owned by" some other object

**make (covered in tutorial): only basic understanding needed of what it does**

* The general format is this:

```make
<target>: [ <dependency> ]
    [ <TAB> <command> <endl> ]
```

Realistically, just memorize how to write one of these:

```make
CXX = g++
CXXFLAGS = -Wall -MMD -g
EXEC = main
OBJECTS = main.o book.o textbook.o comic.o ...
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
    ${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
    rm ${OBJECTS} ${EXEC} ${DEPENDS}
```

**Pure Virtual Methods**

Pure virtual methods are important for the concept of **abstract** classes.

A simple example:

What if we have a `Student` class that has derived classes, `Coop` and `Regular`?

We really have no reason to have a *concrete implementation* of the base class, `Student`.

Hence, we make `Student` abstract. Typically this will be for when you either:

* Don't want any actual instances of a class
* Do not want to implement a method that would never be used for a generic base class

```cpp

class Student {
    public:
        virtual void foo() = 0;
};

class Coop : public Student {
    public:
        void foo() {
            return;
        }
};

class Regular : public Student {
    public:
        void foo() {
            return;
        }
};
```

Note that **ALL MEMBERS ARE INHERITED** so if the pure virtual method is not implemented in the derived class, the derived class will also be **abstract**

**Abstract vs Concrete Classes**

* Classes that contain at least one pure virtual method are considered **abstract**
* Classes that contain no pure virtual methods are considered **concrete**
* 1 to many dependency

**Observer Pattern**

Also known as *publish-subscribe pattern*

We use the terms *subject* and *observer* to describe *publisher* and *subscriber* respectively.

**Subject**: 
    
* Observable, generates data
* Need not know details of the Observer
* Subject "has a" Observer

**Observer**: 

* Observes subject for data and responds to it

Flow:

1. Observers are attached to the subject (`Subject::attach(Observer*)`)
2. Subject's state is updated
3. Subject notifies each observer (`Subject::notifyObservers()`)
4. Each observer responds based on data received (`Observer::notify()`) (actually called by `notifyObservers()` above, but implemented in Observer)

The key thing to note here is:

There is an abstract subject and a concrete subject as well as an abstract observer and a concrete observer.

The abstract subject "has a" array of **abstract** observers.

The concrete observer "has a" **concrete** subject.

To think about this intuitively, the subject need not know the details of the observer. However, the observer can only subscribe to a specific subject as it needs specific data.

The subject just sends data, *trusting* that the `notify` method is implemented as intended. Hence, it only needs to have an array of the base class and call notify on them.

The object needs to subscribe to specific things. Hence, it makes sence that the observer "has a" concrete subject object. Calling "attach" will add the observer into the "list of objects to notify". Whenever the subject changes, it will notify the list of objects that asked to be notified. 

TBH: Just look at and memorize the structure of the ObserverUML pdf in the directory.

Some things to consider:

1. Subject and concrete Subject can be merged
2. If notifying is not enough, we can have the concrete subject implement a `getState` function

**Decorator Pattern**:

Possibly the most intuitive pattern out of all of them.

Basically, we have a plain object, and we add on to that object to fit to what we need using *decorator* classes.

For example:

We have a plain cup of coffee.

Then we add sugar, milk, syrup, and whipped creme.

Instead of having separate classes for every type of combination, we make it closely model the real life interaction of beverage + toppings.

Key thing to make note of is of course, the UML.

We have an abstract *Component* class. This is our base class.

Everything is pure virtual for this abstract Component class.

The concrete Component class will be the "plain" object and it inherits from *Component*.

The abstract *Decorator* class will be the base class for our "decorations".

Decorator is abstract because it doesn't override the pure virtual methods in the Component.

We can have many different concrete Decorations that inherit from this abstract *Decorator* class.

**Factory Method Pattern**

This is for when we want *conditional construction of objects*.

For instance, we have a game that has stages where turtles and bullets are spawned randomly. Instead of calling the constructors randomly, we can put in a "factory method" that creates Enemies.

Layout:

![Picture 1](https://github.com/bryanc208/CS246/blob/master/pic1.png "pic")

We have the Enemy classes on the left. These enemy classes will be generated in the Levels. The `NormalLevel` will generate more `Turtle` objects and the `Castle` will generate more `Bullet` objects. 

The abstract `Level` will have a pure virtual `createEnemy` where each concrete `Level` object will have a different implementation of `createEnemy`.

This is good because we can easily add more enemies and change how a `Level` works without having to go through much troubles. We can also make a `Boss` singleton so that there can only be one boss in each level.

**Template Method Pattern**

* A turtle needs to have a head, shell, and feet.
* We want to change up turtles so that we can maybe just change the shell colour.
* We make the `drawShell()` function pure virtual and then simply override it in the derived classes `RedTurtle` and `GreenTurtle`

![Picture 2](https://github.com/bryanc208/CS246/blob/master/pic2.png "pic")

**Relationship Summary**

![Picture 3](https://github.com/bryanc208/CS246/blob/master/pic3.png "pic")

**Template classes** 

* See example in exam directory

**STL: vector/iterators**

We go over this briefly

```cpp
for (vector<int>::iterator i = v.begin(); i!= v.end(); i++) {
    cout << *i << endl;
}
```

It is basically an abstraction to a pointer. Just like how we were able to do pointer arithmetic in C, we can use iterators to accomplish the same task.

- STL map
**Visitor Design Pattern**

* What if we need to dispatch based on **two** run time types of objects instead of just one?
* The trick is the Visitor Design Pattern with **double dispatch**
* Say we have Enemy and Weapon combinations that need to do different things
* We make an abstract *Weapon* class that overloads the method for each type of **Enemy**
* Each concrete derived **Weapon** class then overrides each overload
* The Enemy passes itself into the Weapon's `strike` method
* Then the Weapon strikes the argument with `*this`, which is itself

- Double Dispatch
- Adding functionality without changing class hierarchy code

**Circular Dependencies: solution: forward declare when possible**

* When A includes B and B includes A

**Compilation Dependencies: when to forward declare vs when to include**

* Class that inherits from A needs to **include** A
* Class that has A as a member needs to **include** A
* Class that has a pointer to an A object can **forward declare**
* Class that has a function that uses A can **forward declare**

General rule of thumb: if at compile time, the code needs to know the exact size of object, we must include it.

**pImpl Idiom**

* Hide away all member data variables that are private
    * Since these are private, there can be no code that depends on it
    * However, any code that includes this header must recompile if any change is made
    * We can mitigate this by the pImpl Idiom
* Create a struct that contains the member data
    * Keep a pointer to an object of that type 
    * We now only need to forward declare the struct `somethingImpl`
 
**Generalize the pImpl Idiom: Bridge Design Pattern**

![Picture 4](https://github.com/bryanc208/CS246/blob/master/pic4.png "pic")

We make the Impl a base class and keep subclasses to implement other details.

This is known as the bridge pattern.

- Revisiting the big three (inheritance)
**Partial Assignment problem**

```cpp
Book *bp1 = new TextBook();
Book *bp2 = new TextBook();
*bp1 = *bp2;
```

This is partial assignment. We are using base class assignment operator to assign derived class objects.

We can make the assignment operator virtual. However, we would need to override it using `Book` as a parameter and not `TextBook`!

This leads to next point.

**Mixed Assignment problem**

Three conditions for mixed assignment:

1. Base class assignment operator is virtual
2. Derived class assignment operator is overriden with base class as parameter
3. Derived class assignment operator is used to assign a derived class object of a different type

i.e.) `TextBook`'s assignment operator is used for a `Comic` object

**Solution without making operator= virtual**

* First the **partial assignment** problem happens if everything was done without any modifications
* So we see that making the assignment operator virtual created a potential for **mixed assignment**
* So now we fix all of this by making the **always** making the base class abstract
* Then we make the assignment operator to be protected
* We can manually assign the base class portion of the object before doing the derived class portion of the object 

**Casting: 4 kinds of casts**

1. `static_cast` - converting pointer of base class to pointer of derived class, or int to float (vice versa)
2. `const_cast` - convert const to variable to mutable variable
3. `reinterpret_cast` - purely a compiler directive which instructs the compiler to treat the sequence of bits of expression as if it had the `new_type`
4. `dynamic_cast` - if cast successful, `dynamic_cast` returns a valud of type `new_type`. If cast fails, returns null pointer

**Exceptions**

* stack unwinding: popping the call stack until a suitable handler is found
* try-catch: try and then catch the exception, handle it
    * If handled, no more code is run

We can rethrow:
    * `throw e` - creates a copy of e then throws
    * `throw` - rethrow without copy

We can also rethrow another type of exception.

**CATCH EXCEPTIONS BY REFERENCE**

* `(...)` will catch all
* Can throw anything (not just Exceptions)

**Common Exceptions**: 

* `out_of_range`: index out of bounds
* `bad_alloc`: call to `new` fails
* `bad_cast`: `dynamic_cast` to a reference fails

- Exceptional Control Flow 

* Sequential execution

- Stack unwinding
- Solution to mixed/partial assignment problem with virtual operator=

* Now we introduce the other solution to the mixed/partial assignment problem
* Instead of making the base class abstract, we can simply do a `dynamic_cast` to change the right side to the right type
* We can override the virtual method as required but simply do a cast before we do anything else

**Three levels of exception safety**

* We can make our code exception safe with the three levels of exception safety:

1. Basic guarantee - program remains in valid state (no memory leak, dangling pointers, etc.)
2. Strong guarantee - if an exception occurs in function f, f leaves the program state unchanged, "as if the function was never called"
3. No throw guarantee - function always succeeds

`auto_ptr`

* stack allocated
* this will call the dtor of `auto_ptr` when an exception is thrown and the pointer will be properly deleted
* **copy constructor takes a non-const reference**
* the copy constructor/assignment operator will **STEAL** the field of the **RHS**
* so the left hand side will take ownership of the pointer on the right

**VTable and Vptr**

* VTable stores addresses to where the code "resides"
* Each object will now contain a **vptr** which stores a pointer to the **VTable** of the class
* There is one **VTable** per class
* When a function call occurs for virtual methods, the address of the method to call is "lookped up" to get the correct code to execute
* All virtual methods must be implemented to create a concrete class since otherwise we would try to dereference a **NULL** pointer!
* Cost is 8 bytes per each object created

- superficial knowledge of Return Value Optimization (RVO)


