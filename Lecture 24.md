#Lecture 24 - Dec. 3, 2015

Exception Safety, How virtual works

## Exception Safe Code

Quick tip:

* Do not let destructors throw an exception
* Can lead to multiple simultaneously live exceptions

**RAII**: Resource Acquisition is Initialization

Every resource should be wrapped in a stack allocated object whose job is to release that resource.

C++03 provides a template class `auto_ptr`.

* The constructor expects a pointer to dynamic memory
* The destructor will call delete on the underlying pointer

```cpp
void f() {
    auto_ptr<MyClass> P(new MyClass);
    MyClass q;
    g();
}
```

Notice that the `auto_ptr` is a stack allocated object. If any exception is thrown, the stack allocated object will be destroyed and the destructor will be called, effectively deleting the pointer to the MyClass object.

The copy constructor/assignent operator will **steal** the field of the RHS. This is to avoid double free-ing. **This is a rare case when the copy constructor takes a non-const reference**.

**SEEMS LIKE THIS CONCEPT WILL BE ON THE FINAL**

C++11 calls this `unique_ptr`.

C++03 `tr1::shared_ptr` is like `unique_ptr` but allows multiple references to the same resource and still does not run in to problems of double free.

## Levels of Exception Safety

There are three levels. **On the exam**

1. Basic guarantee
2. Strong guarantee
3. No throw guarantee 

**Basic guarantee**:

If an exception occurs, the program still remains in a valid state. i.e.) An exception will not cause a program or function to be in an **invalid** state (memory leak, dangling pointers, etc.)

**Strong guarantee**:

If an exception occurs in function f, f leaves the program state unchanged, "as if the function was never called".

**No throw guarantee**:

Function always succeeds.


Example of question:

```cpp
Class A {---};
Class B {---};
Class C {
    A a;
    B b;
    void f() {
        a.g();  // suppose g has a strong guarantee
        b.h();  // suppose h has a strong guarantee
    }
};
```

Consider this argument:

Suppose `g()` launches a rocket and it was successful. Now suppose `h()` fails. An exception is thrown by `h()` and `f()` cannot satisfy the requirement of a strong guarantee because the program state was changed by a *successful* execution of `g()`.  `f()` has a *non-local side effect*. So there cannot be a strong guarantee made by `f()`.

The distinction that is made here is that when `g()` **fails**, it leaves the program unchanged. 

In this case, `f()` would keep the program unchanged if both `g()` and `h()` fail!

An attempt to make `f()` have a strong guarantee is shown below:

```cpp
void C::f() {
    A tempa = a;
    B tempb = b;
    tempa.g();
    tempb.h();
    a = tempa;
    b = tempb;
};
```

This seems okay! However, there is another problem. What if the assignment operator fails at the last 2 lines of `f()`?

So here is the final version of `f()` to make it have a strong guarantee:

```cpp
struct CImpl {
    A a;
    B b;
};

class C {
    auto_ptr<CImpl> pImpl;
    void f();
};

void C::f() {
    auto_ptr<CImpl> temp(new CImpl(*pImpl));
    temp->a.g();
    temp->b.h();
    std::swap(pImpl, temp);
}
```

## VTable

We know that virtual methods do dynamic dispatch: the method that is called is decided by the type of the object at run-time. How does that work?

```cpp
Book *b;
    if () b = new Textbook;
    else b = new Comic;
b->isItHeavy();
```

We now introduce the concept of a vtable. 

Static dispatch works as follows: a function call(same for non-virtual method) loads the address of the memory containing the code. Then it executes a jump to that address. 

Virtual methods create something called a *VTable*.

The VTable stores addresses to where the code "resides". Each class has its own VTable and there is one per class.

Each object will now contain a *vptr* which stores a pointer to the *VTable*.

When a function call occurs for virtual methods, the address of the method to called is "looked up" in the respective *VTable* to get the correct code to execute.

Now we know why all virtual methods must be implemented to create a concrete class. Otherwise, the function call will try to derefence a NULL pointer to a function which would cause errors!

The cost associated with virtual methods is the cost of adding an additional pointer to each instance of that class. This can be either 8 or 16 bytes depending on the architecture.
