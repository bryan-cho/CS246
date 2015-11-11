#Lecture 16

Friends, system modeling (composition, aggregation, inheritance) 

Last time: Encapsulation - make fields private
 - maintain class invariants
 - flexibility to change implementation


```cpp
class Vec{
    int x,y;
    public:
        Vec(...)
        int getX() const{ return x; } // Accessor (getter)
        int getY() const{ return y; }
        void setX(int v) {x = v; } // Mutators (setters)
        void setY(int v) { y = v; } 
}
```

Suppose
- private fields
- no accessors
- want an output operator

C++ provides the "friend" keyword

```cpp
class Vec{
    int x,y;
    public:
        friend std::ostream &operator<<(...);

};
ostream &operator<<(ostream &out, const Vec &v){
    out << v.x << v.y;
    return out;
}
```

## System Modelling

- identifying the abstractions / entities (classes)
- relationship between entities/classes

UML: Unified Modeling Language 

- a class in UML is a box with 3 sections
- first section has a class name
- Other 2 are optional
- second section is for fields 
- third section is for methods
 + public
 - private

### Relationship between classes

**Composition**: embed an object within another object

```cpp
class Vec{
    int x,y,z;
    public:
        Vec(int x, int y, int z): x(x), y(y), z(z){}
};

class Plane{
    Vec v1,v2;
};

int main(){
    Plane p;
    // WONT COMPILE because no zero argument constructor
}
```

1. Provide a 0 param constructor
2. Pre-empt the call to the 0 param constructor of Vec by calling some other constructor
   Plane::Plane: v1(1,2,3), v2(4,5,6){}
   Plane p; // Will compile

The composition relationship creates a "owns a" relation
A "owns a" B if 
- if B cannot exist on its own
- if A is destroyed B is destroyed
- if A is copied B is copied

##Aggregation

Analogy: parts in a catalog, ducks in a pond

A "has a " B
 - if when A is destroyed, B continues to live
 - if A is copied, B is not copied

```cpp
class Pond{
    Duck * duck [MAXDUCKS];
}
```

##Inheritance

Book
- title
- author
- numPages

TextBook
- title
- author
- numPages
- topic

Comic
 - title
 - author
 - numPages
 - protag

Collection of any type of Book
 - array of `void*`
 - union type

**Inheritance**: creates "IS A" relationship

TextBook "IS A" Book with an additional `topic`

Comic "IS A" Book with an additional `protagonist`

(Base Class / Super Class / Parent Class) 

Book
 - title
 - author
 - numPages
 - +getAuthor

(Derived Class / Sub Class / Child Class)

Inherits from Book.

TextBook 
 - topic

Comic
 - protagonist

Derived classes inherit **everything** from the base class

```cpp
int main(){
    TextBook tb;
    tb.getAuthor();
    tb.author = "Nomair"; XXX THIS DOESNT WORK
}
```

```cpp 
TextBook::addAuthor(string auth){ author += auth; }
```

TextBook has inherited private author // NOOOOOO WILL NOT COMPILE

Private really means Private

```cpp
TextBook::TextBook(string t, string a, string n, string topic): title(t), author(a), numPages(n), topic(topic){} // This shit doesnt compile
```

When an object is created

1. space is allocated
2. super class part of the object is created
3. field initialization
4. constructor body

```cpp
TextBook::TextBook(string t, string n, int n, string topic): Book(t, a, n), topic(topic){}
```

Same space filled by 2 different constructors

Protected: 

- only code in this class or subclasses
- accessible by code in defining class and sub classes


