# Lecture 18 - Nov. 12, 2015

Design Patterns, Observer, Decorate, Factory

## Observer Pattern

Pubsub.

**Publisher/subject** - generates data

Abstract Subject class: (Publisher)

* `attach` - subscribe to event
* `deetach` - unsubscribe to event
* `notifyObservers` - when something happens to a subscribed event, notify the subscribers
* "Has a" relationship with Abstract Observers (Subscribers)
    * Has an array of pointers to Abstract Observers
* Virtual destructor, `~AbstractSubject()` makes it abstract

Rule of thumb: to make an abstract class but you don't need to make any of its methods pure virtual, make the destructor pure virtual.

**Note**: 

* If we make the destructor to be pure virtual, we need to provide an implementation for that pure virtual destructor
* This is because any derived class being destroyed will call the destructor of a parent class
* We define the method to be pure virtual in the header file, and then provide an implementation in the `.cc` file.

 
Concrete Subject  class:

* has its own `getState` implementation
* inherits `notifyObservers` from abstract class 

**Subscriber/observer** - consumes data

Abstract Observer class: (Subscriber)

* `notify` - notifies subscribers - pure virtual
* a virtual destructor

Concrete Observer class:

* Instance of abstract observer class
* Will have its own `notify` implementation
* "Has a" Concrete Subject object member stored as a pointer

1. Concrete Observer (Subscriber) will call `attach` on a Concrete Subject (Publisher).
2. Concrete Subject (Publisher) will save pointer of Concrete Observer.
3. New event happens, Concrete Subject calls `notifyObservers`
    * Goes through **Abstract** Observer (Subscriber) pointers
    * Calls `notify` on for each object 

The benefit of abstract classes provides us modularity and flexibility to create new observers and subjects easily.

### Implementation:

In essence, the Abstract Subject (Publisher) class just needs to hold a bunch of Abstract Observer pointers, and be able to invoke `notify` on each of them.

The concrete Observer will attach itself to the Subject on creation.

When an event happens, the subject will call `notifyObservers`.

Based on the implementation of `notify`, the observer will do something based on the notification.

## Decorator Pattern

Add to a pre-existing object

We have a base class *Component* which is an abstract class.

Then we have two classes that inherit from *Component*: ConcreteComponent and *Decorator*, another abstract class.

The ConcreteComponent is the basic component, such as a plain window in a browser.

The *Decorator* abstract class **is a** component and **has a** component at the same time.

The idea is, that the Decorator object will *wrap* around the ConcreteComponent object and add to it.

e.g.) Scroll bar, menus, etc.

The difference between a ConcreteComponent and a Decorator is the pointer to the *Component*.

Another example:

Coffee and Toppings.

The key thing to realize is that Coffee (ConcreteComponent) and the Toppings (Decorator) are almost exactly the same.

The only difference is that each Topping object will possess a pointer to the Coffee (Component) for which it decorates.

## Factory Pattern

The type of the object being created depends on the state of the program.

Suppose we have a game.

We might have an abstract class Level, which has subclasses Normal and Hard.

The Normal Level might generate less Enemy objects, while the Hard Level might generate more Enemy objects.

This is advantageous because the main game loop need not be altered. The only change that needs to be made when we want to add new logic to generate Enemies can simply be an addition of a concrete Level class.

We can also implement more Enemies easily.
