# Lecture 14 - Oct. 29, 2015

Assignment operator, methods vs. functions, arrays of objects

## Assignment operator

The assignment operator can only be defined as a method.

Other operators must be implemented as a function.

```cpp
Student billy(60,70,80);
Student jane;
jane = billy;
jane.operator=(billy);
```

Assignment operator is right associated, unlike other operators.

```cpp
struct Node {
    int data;
    Node *next;
}

Node& Node::operator=(const Node &other) {
    if (this == &other) return *this;                          // self-assignment check
    this->data = other.data;
    delete this->next;
    this->next = other.next ? new Node(*other.next) : nullptr; // what if 'new' fails?
    return *this;
}
```

Assignment operator is fundamentally different from copy constructor.

Copy constructor make an entirely new object.

Assignment operator makes changes to an existing object.

*Self Assignment*: `*np = *np`.

In the above code, if we don't have the top part, we could delete the object itself and lose everything. 

We do something called a "self assignment check" shown on line 27.

We can also improve the above even further by making it "exception safe".

```cpp
Node& Node::operator=(const Node &other) {
    if (this == &other) return *this;
    Node *tmp = next;
    next = other.next ? new Node(*(other.next)) ? nullptr;
    data = other.data;
    delete tmp;
    return *this;
}
```

### Copy and Swap Idiom

```cpp
void Node::swap(Node &other) {
    int temp = this->data;
    this->data = other.data;
    other.data = temp;
    Node *tempNext = this->next;
    this->next = other.next;
    other.next = tempNext;
}

Node& Node::operator=(const Node &other) {
    Node temp = other;              // copy constructor (relies on deep copy constructor)
    this->swap(temp);
    returh *this.
}
```

Once the assignment operator goes out of scope, the temp copy will be destroyed.

This will give you full marks on the final, even if the constructors are not properly implemented.

We can also just take in the `other` by value, and remove line 73.

Some improvements:

```cpp
Node& Node::swap(Node &other) {
    int temp = this->data;
    this->data = other.data;
    other.data = temp;
    Node *tempNext = this->next;
    this->next = other.next;
    other.next = tempNext;
    return *this;
}

Node& Node::operator=(Node other) {
    return this->swap(other);
}
```

## Rule of Three

If you need to write a custom version of:

    * copy constructor
    * destructor
    * operator=

You usually need to implement all three

## Overloading Operators: Functions vs. Methods

`operator=` must be implemented as a method.

* `operator=` is already implemented by default for a class

Other operators that must be implemented as a method:

* `operator[]`
* `operator->`
* `operator()`
* `operatorT()`
* `operator=` 

The first four, there is no technical reason that they must be implemented as a method.

When an operator is implemented as a method, the `this` parameter is implicitly passed as an argument.

```cpp
Vec v1(1,2), v2(3,4);
Vec v3 = v1+v2;

Vec Vec::operator+(const Vec &rhs) {
    Vec v(this->x + rhs.x, this->y + rhs.y);
    return v; 
}

Vec v4 = v3*5;

Vec Vec::operator*(int k) {
    Vec v(this->x * k, this->y * k);
    return v;
}

Vec v5 = 5*v4;          // <-- this one must be implemented as a function
                        // We cannot do 5.operator*(v4);

Vec operator*(int k, const Vec &v) {
    return v*k;
}

ostream& Vec::operator<<(ostream &out) {
    out << this->x << " " << this->y;
    return out;    
}

// If we do this, then we have to do: v2 << (v1 << cout)
// If we want to do cacading
```

This is why certain operators should be implemented as functions.

## Arrays of Objects

```cpp
struct Vec {
    int x, y;
    Vec(int x, int y): x(x), y(y) {}
}

Vec vectors[3];                     // Doesn't compile (no default constructor)
Vec *myVecs = new Vec[num];         // Doesn't compile
```

We work around this by:

Option 1: Providing a 0 parameter constructor
    * May not always be feasible

Option 2: Stack allocated array: use array initialization.

```cpp
Vec vectors[3] = { Vec(1,2), Vec(3,4), Vec(5,6) }
```

Option 3: Heap allocated: create pointers to objects (these can be left null until needed)

```cpp
Vec *vectors[10];               // stack allocated array of Vec pointers

vectors[0] = new Vec(1,2);      // free the pointers, but not the array itself

Vec ** vecs = new Vec*[num];    // heap allocated array of Vec pointers

vecs[0] = new Vec(1,2);

for(int i=0; i<vecs.size(); i++) {
    delete vecs[i];
}
delete[] vecs;
```
