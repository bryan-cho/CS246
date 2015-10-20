# Lecture 9 - Oct. 13, 2015

Reviewing C concepts.

Notice the difference between `const int *p` and `int * const p`

`const int *p` is a pointer to a constant integer.

`int * const p` is a constant pointer to an int. You can manipulate the value of the int but you cannot change the address that the pointer points to.

Tip: read from the variable to the left.

Rule: `const` applies to the thing on the left unless there is nothing to the left, then it applies to the right.

### References

Note about references: they are constant.

Cannot change what the reference points to.

Think of it as: **constant pointer with automatic dereferencing**.

A reference is an **alias**. It is another name for what it is referencing.

Reference cannot be uninitialized.

Cannot create:

* Pointers to a reference
* Reference to reference
* Array of references

Remember to declare references as **const** if the value need not change. (MARKS MAY BE LOST IF NOT DONE).

### When to allocate memory in the heap

Always allocate on the stack unless:

1. The value must outlive the variable scope
2. If size of collection/array is unknown or subject to resizing
3. Memory allocation is too big for the stack
