# CH 9 Classes A Deeper Look

Objectives:

 1. Separate the class's interface from its implementation for reuse.

 2. include guard in a header to prevent code from being included in the same source code file more than once.

 3. use "ostringstream" to create string representation of the time in standard and universal time format.

 4. explain the compilation and linking process from the standpoint of the class-implementation programmer , the client-code programmer and application user.

 5. how client code can access a class's public members via :
    - name of object and dot operator (.)
    - reference to an object and dot operator (.)
    - pointer to an object and the arrow operator (->)

6. the access functions that can read or write an object's data members:
    - predicate functions : test conditions
    - helper functions : private member function that support operation of the class's public member function , but not intended for use by clients of the class.

7. default arguments can be used in constructors to enable client code to initialize objects using a variety of arguments.

8. a member function called destructor that's part of every class and use to preform a termination housekeeping on an object before it's destroyed.

9. show that returning a reference or a pointer to private data breaks the encapsulation of the class , by allowing the client code to directly access an object's data.

10. use a default memberwise assignment to assign object of a class to another object of the same class.

11. we use const objects and const member functions to prevent modification of objects and enforce the principle of least privilege.

12. we discuss composition : a form of reuse in which a class can have objects of other classes as members.

13. use friendship to specify that nonmember functions can also access a class's non-public members - a technique used a lot with operator overloading.

14. discuss "this" pointer, which is an implicit argument in all calls to a class's non-static member functions, allowing them to access the correct object's data members and non-static member functions

15. we motivate the need for static class member functions and show how to use them in your own classes

