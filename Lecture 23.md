# Lecture 23 - Dec. 1, 2015

Exceptions

Last class, we talked about `dynamic_cast`. Recall that `dynamic_cast` returns `NULL` if the cast is not possible.

What happens when we `dynamic_cast` and assign the result to a reference? References cannot be `NULL`.

When this occurs, an exception is thrown.

## Exceptions

When an error occurs an exception is raised/thrown.

An unhandled exception will cause the program to terminate by default.

The way exceptions work is by "travelling" all the way back up the stack chain until a try block is found. This is known as **stack unwinding**.

**Stack unwinding**: the process of popping the call stack until a suitable handler is found.

If no handler is found, the exception will "travel" all the way back up to `main` and the default behavior at this point is to terminate the program.

We introduce the `try-catch` block.

**try-catch block**:

```cpp
try {
    // code to protect against exception of type T
} catch (T exception) {
    // code to handle exception of type T
}
```

Something to note is that when an exception is raised, the execution continues after the catch block.

```cpp
try {
    cout << "Start" << endl;
    //code that raises exception
    cout << "Hello" << endl;        // not executed
} catch (T exception) {
    cout << "Exception of type T was thrown << endl;
}

cout << "Done" << endl;
```

This will output the following:

```
Start
Exception of type T was thrown
Done
```

See that `"Hello"` is not printed!

**throw**:

We can explicitly throw exceptions.

There are multiple things we can do when handling an exception:

```cpp
try {
} catch (SomeException e) {
}
```

We can:

1. `throw SomeOtherException(---);`
2. `throw e`
3. `throw`

The difference between 2 and 3 is subtle.

2 and 3 are both throwing the caught exception again. However, 2 is making a copy of `e` and 3 is simply throwing the same `e`. We may lose subtype information if we choose to do 2.

Another way we can get around this is to catch the exception *by reference*.

General advice:

1. To rethrow, just write `throw`
2. `catch` by reference

#### exception Class

All exceptions in the std C++ library inherit from the `exception` class.

In C++, user defined exceptions do not have to inehrit from the `exception` class.

What happens if we want to catch **all** exceptions? 

There is special syntax for this case.

```cpp
try {

} catch (...) { // all possible exceptions caught

}
```

We use `...` to catch all possible exceptions.

You can throw anything in C++ (ints, char, etc.)

**Exceptions are much slower** than other control flow statements.

Advice: create an exception class.

Common exceptions:

* `out_of_range`: index out of bounds
* `bad_alloc`: call to `new` failes
* `bad_cast`: `dynamic_cast` to a reference fails

#### Sequential Execution

```cpp
class BaseException {};
class DereivedException : public BaseException {};

DerivedException d;
BaseException &b = d;
try {
    throw b;
} catch (DerivedException &) {

} catch (BaseException &) {

} catch (...) {

}
```

The catch blocks will be ran sequentially, so the first block to catch the exception will run first and none other will be run.

In the above case, the `BaseException` block will run because the **declared type** of `b` is a `BaseException`.

#### Assignment Operator 

```cpp
Book *b1 = new TextBook(--);
Book *b2 = new TextBook(--);

*b1 = *b2;
```

Recall that to fix the problem of mixed assignment (making base class assignment operator virtual requires same parameter which allows any derived class to be assigned to any base class) we used a `dynamic_cast`.

```cpp
TextBook& TextBook::operator=(const Book& other) {
    TextBook& tother = dynamic_cast<TextBook&>(other); // fixes mixed assignment

    Book::operator=(other);
    topic = tother.topic;
    return *this;
}
```

Notice that if the above fails, we will get a `bad_cast` exception!

We are shifting the responsibility to the caller the assignment operator. The assignment operator will work properly when used properly.

#### Exception Safe

We want to write exception safe code. That is, exceptions should not cause memory leaks, dangling pointers, etc.

```cpp
void foo() {
    MyClass *p = new MyClass;
    MyClass q;
    bar();       // <-- what happens if bar() throws an exception?
    delete p;
}
```

C++ guarantees that during stack unwinding, all stack allocated data will be destroyed.

One way to write the above code to be exception safe is the following:

```cpp
void foo() {
    MyClass *p = new MyClass;
    MyClass q;  // "pretending" no exception raised
    try {
        bar()
    } catch (...) {
        delete p;
        throw;          // partial recovery
    }
    delete p;
}
```
