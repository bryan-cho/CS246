# Lecture 19 - Nov. 17, 2015

Template Method Pattern, C++ Templates, STL

## Template Method Pattern

```cpp
class Sort {
    private:
        input();
        output();
    public:
        Sort()
        virtual doSort()=0;
}

Sort *s = s->sort();
```

Notice that nothing is virtual except `doSort()`.

If we want to implement different sorting algorithms, all we must do is implement the `doSort()` for various algorithms.

This is similar to what was done in A4Q1 where we had two types of lists, `Sorted` and `Unsorted` which only differed in the way it added elements.

The only thing we must do when implementing `Sorted` and `Unsorted` is implement the `add()` method and all other things are inherited.

Let's see this in action with a game example:

Suppose we have a base `Enemy` class. 

We might have another abstract class, `Turtle`.

The concrete implementations of `Turtle` are `Red` and `Green`.

```cpp
class Turtle : public Enemy {
    public:
        void draw() {
            this->drawHead();
            this->drawShell();
            this->drawTail();
        }
    private:
        void drawHead() {---}
        void drawTail() {---}
        virtual void drawShell()=0;
} 

class Red : public Turtle {
    private:
        void drawShell() {---}
}
```

Notice that the individual draw methods are **private**. This is because we do not want people to draw just a head, or just a tail. We want the full turtle to be drawn at all times.

Now, the important part is `virtual void drawShell()=0;`.

Notice that almost everything is already "filled out" in the "template" which is `Turtle`.

The head and the tail is common among all concrete `Turtle`s.

The only thing that will differ is the shell color which should be independently implemented by the concrete `Turtle` classes.

This is a  horrible example (no one would actually implement a new concrete class to change the color of a shell)  so we look at `Sort` which is an example that makes more sense.

Going back to `Sort`, we see that this is almost exactly the same.

`Sort` will take care of the `input()` and `output()` and is essentially saying, "Just provide the sorting algorithm, I'll take care of the rest."

## C++ Templates

**NOTE**: C++ Templates and the Template Method Pattern are irrelevant to each other

**Template class:** generalization by parameterizing class on one or more types.

```cpp
class Node {
    private:
        int data;
        Node<T> *next;
    public:
        Node(int data, Node *next);
        int getData() const { return this->data; }
};

template <typename T>
class Node {
    private:
        T data;
        Node *next;
    public:
        Node(T data, Node<T> *next) : data(data), next(next) {}
        T getData() const { return this->data; }
};
```

Notice that converting to a template is as simple as replacing any occurrence of a concrete type (`int`) from the first class definition with `T`.

The only other catch is that the whenever we used `Node`, we must replace it with `Node<T>`.

We now do:

```cpp
Node<int> *intList = new Node<int>(2, new Node<int>(3, NULL));
Node<char> *charList = new Node<char>('a', new Node<char>('b', NULL));
```

Terminology: using a template with a specific type is called **specializing** a template.

## Standard Template Library (STL)

List of things we can use:

* `std::vector`
    * v[i] <-- can go out of bounds
    * v.at(i) <-- checks for range [0, size-1]
* `std::map`
    * Associative List (Hash Table)
    * Can use any (key, value) pair

####Iterator type

Recall in CS136:

```cpp
int arr[size];
for(int *p = arr; p<arr+size; ++p) {
    //do stuff
}
```

Similar to this, we can iterate through structures in STL using the `iterator` type.

```cpp
for(vector<int>::iterator it = v.begin(); it!=v.end(); ++it) {
    std::cout << *it << std::endl;
}
```

`iterator` is just an abstraction of pointers.

Here is an example of reverse iterators:

```cpp
for(vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it) {
    std::cout << *it << std::endl;
}
```

