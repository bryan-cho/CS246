#Lecture 20 - Nov. 19, 2015

Visitor Design Pattern, Compilation Dependencies

## Visitor Design Pattern

What if we have a situation where we want to do dynamic dispatch on methods but also parameters?

For example:

```cpp
Player *p = ---;
while(p->notDead()) {
    Enemy *e = ---;
    Weapon *w = p->chooseWeapon();
    // Use the weapon on enemy
    e->strike(*w);
}
```

In this case, how does the compiler know which weapon to use? How do we decide whether `strike` is striking the enemy with a *stick* or a *rock*?

We might go about this by "checking" for the type by keeping a `type` member in the `Weapon` class. Then we could check for the type of the `Weapon` at run time. 

A better approach can be done with the **visitor design pattern**.

This can be solved by clever overloading.

```cpp
class Enemy {
    public:
        virtual void strike(weapon &w) = 0;
};

class Turtle : public Enemy {
    public:
        // *this is known to be Turtle at compile time
        void strike(Weapon &w) { w.useOn(*this); }
};

class Bullet: public Enemy {
    public:
        // *this is known to be Bullet at compile time
        void strike(Weapon &w) { w.useOn($this); }
};
```

The significance of what the type of `*this` is known by at compile time is that we must write multiple implementations of `useOn` that takes different types for arguments.

```cpp
class Weapon {
    public:
        virtual void useOn(Turtle &)=0;
        virtual void useOn(Bullet &)=0;
};
```

Basing our choice of method to execute on the runtime type of 2 pointers.

Another example:

Consider the case when we have the following:

Book - base class, contains protected `author` field

Textbook - derived class, contains protected `topic` field

Comic - derived class, contains protected `protagonist` field.

```cpp
map <string, int> catalog;
Book *collection[100];
for (--collection--) {
    collection[i]->update();
}

class Book {
    public:
        virtual void accept(BookVisitor &v) {
            v.visit(*this);    
        }
};

class Textbook : public Book {
    public:
        void accept(BookVisitor &v) {
            v.visit(*this);
        }
};

class Comic : public Book {
    public:
        void accept(BookVisitors &v) {
            v.visit(*this);
        }
};

class BookVisitor {
    public:
        virtual void visit(Book &b)=0;
        virtual void visit(Textbook &t)=0
        virtual void visit(Comic &c)=0;
};
```

This is useful for developing libraries. The code needs to be "prepared to accept visitors".

**NOTE**: Forward declare classes unless you can't. This avoids circular inclusions.

We will talk about **when** we can avoid `#include` next class.
