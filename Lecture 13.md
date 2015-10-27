# Lecture 13 - Oct. 27, 2015

"The Big Three", Copy Constructor, Destructor, operator=

## Copy Constructor

Used to construct a new object as a copy of an existing object.

```cpp
Student billy(60, 70, 80);
Student bobby = billy;
```

There is a built-in copy constructor.

Every class "comes with": 

* Default constructor **(goes away when you write your own constructor)**
* Copy constructor
* Destructor
* Copy assignment operator

For a class C, the copy constructor takes one parameter: const reference to object.

```cpp
class C {
    public:
        C(const C &other) {}; //convention is to use other or rhs (right hand side)
}
```

An example of this is shown with the Student class:

```cpp
class Student {
    private:
        int assignments;
        int midterm;
        int final;
    public:
        Student(const Student &other) 
        : assignments(other.assignment)
        , midterm(other.midterm)
        , final(other.final) {}
}
```

The copy constructor shown above is the same behavior as the built-in copy constructor.

Consider the following:

```cpp
class Node {
    private:
        int data;
        Node *next;
    public:
        Node(int data, Node *next) 
        : data(data)
        , next(next) 
        {}
        Node(const Node &other)
        : data(other.data)
        , next(other.next)
        {}
};

Node *np = new Node(1, new Node(2, newNode(3, nullptr)));
Node m = *np;                 //copy constructor
Node *npCopy = new Node(*np); //copy constructor

//68: np[-]--> [1|-]--> [2|-]--> [3|/]
//69: m[1|-]-------------^ points to *np's next instead of doing a deep copy
//70: npCopy[-]-->[1|-]--^ similarly, points to *np's next 
```

The default copy constructor does a shallow copy.

We often want a "deep copy" when an object contains fields that are dynamically allocated (i.e. on the heap).

What we should do is the following:

```cpp
class Node {
    private:
        int data;
        Node *next;
    public:
        Node(const Node &other) {
            this->data = other.data;
            if (other.next == nullptr) {
                this->next = nullptr;
            } else {
                // Need to dereference, we send in a Node object.
                this->next = new Node(*(other.next));
            }
        }
}
``` 

This will do a deep copy of the linked list.

We show an alternative way of writing the copy constructor:

```cpp
class Node {
    private:
        int data;
        Node *next;
    public:
        Node(const Node &other)
        : data(other.data)
        , next(other.next ? new Node(*(other.next)) : nullptr)
        {}
}
```

Places where a copy constructor is called:

1. Creating an object as a copy of another
2. When an object is passed by value
3. When an object is returned by value (returning a stack allocated object)

We must pass in a const reference to a copy constructor.

This is because if we pass in the object by value, the copy constructor will be invoked each time.

### Single Parameter Constructors

```cpp
class Node {
    public:
        Node(int data)
        : data(data)
        , next(nullptr) 
        {}
}

void foo(Node n) {}

Node n(4);  // valid
foo(n);     // valid

Node m = 4; // valid
foo(4);     // valid
```

Single Parameter Constructors create implicit conversions.

```
string str = "hello";
```

`std::string` has a 1 parameter constructor

Does an implicit conversion from `const char * --> std::string`

We can use the `explicit` keyword to disable this behavior.

```cpp
class Node {
    public:
        explicit Node(int data)
        : data(data)
        , next(nullptr) 
        {}
}
```

Now this will make

```cpp
Node m = 4; // invalid
foo(4);     // invalid
```

## Destructor

When an object is destroyed, a special method called the destructor runs.

Stack allocated object is destroyed when it goes out of scope.

Heap allocated object is destroyed when it is deleted.

* A class only has one destructor
* 0 parameter method (no return type)

The name of a destructor is the name of the class prefixed with ~.

* You get a built-in destructor with every class.
    * Calls the destructor on any fields that are objects

```cpp
Node *np = ...;

// np -->[1|-]-->[2|-]-->[3|/]

delete np;

struct Node {
    int data;
    Node *next;
    ~Node() {
        delete next;
    }
}
```

Calling delete on `NULL` is safe.

The call to a `nullptr` will be what terminates the recursive execution of the destructor.

## Separate Compilation

**Recall**: we split our programs into

.h files (type definitions)         .cc files (function implementations)

In the header files, we should now include method headers.

In the implementation files, we now should include method implementations.

The way we implement methods is by using this notation:

```cpp
(Class name)::(Method name)() {}

Node::Node() {}
void Node::push(int val) {}
int Node::pop() {}
...
etc.
```

## Assignment Operator

`Student bobby(billy);` copy constructor

`Student jane;` 0 parameter constructor

`jane = billy` updating an existing object to be a copy of the existing object
