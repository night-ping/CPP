# CH 9 - Classes A Deeper Look

## 9.2 Time Class Case Study: Separating Interface From Implementation

- previously, we placed complete class definition in a header file and include it in a source file `main()` to use that class .. this approach works, but it also **exposes** the class's full implementation to anyone who reads the header.

- this violates a core principle of SWE : information hiding

- the problem is if the client know how a class works internally , they might depend on those details in their own code. and later if the class implementation changes, client code may break because it was tied to internal behavior.

- so hiding implementation allows the class to change internally without forcing client code to change (as we can!).

- the client only need to know :
    1. available member functions (interface)
    2. argument you can pass for each function
    3. return type for each function

- the client doesn't need to know how those functions are implemented

- the solution for this is by separating the interface (what it does) in a header file from implementation (how it does it) in source code file

- don't forget to add a header guards to prevent multiple inclusions of the same file within a single translation unit (google it for more)

```c++
#ifndef TIME_H
#define TIME_H
// class definition here
#endif
```

### 9.2.1 Interface of a class

what the concept of Interface?
- well, interface defines how two entities can interact together .. it specifies **what actions** can be performed, but **not how** those actions are carried out internally (the general idea of interface)

- you use an interface every day .. think of TV remote it very clear and simple of what you can do with it and how to use it, but you don't know what the internal mechanism how actually the tv remote work .. you don't know actually you don't care to know how it works inside and this is one of goals of interface
- this actually can take us to a good idea that says .. all tv remote almost offer the same operations, but each may implement them differently. again, we don't care as long as it work well it's fine

- applying this to classes , the interface of a class defines:
    1. what services the class provides (functions)
    2. how clients can request those services

- the class's public interface are functions in public section

- you can define a class's interface by writing :
    1. member-functions prototypes (no implement yet)
    2. data member declarations , usually set private

- separating interface from implementation provide 3 main benefits:
    1. reusability - the class can be reused in other programs
    2. clarity for clients
    3. infotmation hiding

### 9.2.3 - 9.2.4 Time class definition and Time class member functions

- our first example found in project named **TIME** which is 3 files:
    1. Time.h : contains Time's class definition
    2. Time.cpp : contain Time's member functions definition
    3. main.cpp : client code


- the header need to included in the client code to ensure that the client code calls the member functions of class correctly

### 9.2.5 Scope Resolution Operator

- `::` used when defining member functions outside the class definition
- it connects each function definition back to its class declaration.. it tells the compiler that this function is belongs to that class
- without the compiler consider them a global functions not a member of a class which in turn cannot access private data members of the class or call member functions and must use an object to access members

### 9.2.6 Including the Class Header in the Source-Code File

- why we need to include the header in the source code file ??

    1. ensure that functions definition match their prototypes (compiler verify)
    2. to access class data members


### 9.2.7 setTime member function and throwing exceptions

- setTime has its validation logic to ensure it take only valid values of time
- if there's wrong it will throwing an exception it notify the client code that an invalid value was passed to setTime

- How the Exception works?
    1. throw statement creates an object of type `invalid_argument` using its constructor
    2. the constructor accepts a custom error message string
    3. immediately terminates the setTime function
    4. passes the exception to the caller (client code)
    5. the client can handle it using `try..catch` block to recover it

- by this Time object cannot have invalid values , how ?
    1. default constructor initialization when time object created , its constructor initialized all members to 0
    2.any attempt to change the time must go through setTime which validates all new values and throws exceptions for invalid

### 9.2.8 toUniversalString member function

- what the use of `ostringstream`?
    - `ostringstream` works like `cout`, but instead of printing to the screen , it writes formatted output into a string stored in memory of that object
    - to retrieve the resulting call the str() member function

### 9.2.12 using class Time

- once you define a class :
    1. create object from it
    2. create array of object of this type
    3. create a reference to time object
    4. create a pointer to time object

- separating the interface from the implementation doesn't affect the way that this client code uses the class , it affects obly how the program is compiled and linked

### 9.2.13 Object Size

- each object in memory only contain data members - the actual data values that make each object unique.

- the member functions are not duplicated for every object, all object share the same set of member functions
- the functions exist only once in the program's code segment, and all objects can call them .

## 9.3 Compilation and Linking Process

- we can imagine it as 3 roles :
    1. class-implementation programmer :
        - create 2 files Time.h and Time.cpp
        - compile Time.cpp, the result is Time.o (object file contain machine code)
        - provide the interface and object code (hide all implementation details)
    2. client-code programmer
        - need Time.h , Time.o , C++ standard library
        - create main.cpp, compile and the result is main.o
        - linking step take all compiled pieces and STD lib and produce the final exe program
    3. end-user (how runs the final executable)
        - use Time.exe result from linker step

## 9.4 Class Scope and Accessing Class Members

- every class defines its own scope, which means that :
    - the data members and member functions belong to the class itself
    - anything declared inside a class is **visible** to other member of the same class
    - in constrast , Nonmember functions exist in the global namespace scope (not associated with any class)

- Inside class scope all member functions can access the class's data members even private ones directly **by name** there's no need to access it through an object like `objName.hour`, just `hour`

- outside class , you can access the class's **public members only**, and you must use something called handle to do so.
- handles can be (object name, reference to an object, pointer to an object)

```c++
Account account;                 // an Account object
Account& accountRef{account};    // reference to account
Account* accountPtr{&account};   // pointer to account


account.setBalance(123.45);      // using the object
accountRef.setBalance(123.45);   // using a reference
accountPtr->setBalance(123.45);  // using a pointer
```

## 9.5 Access Functions and Utility Functions

- Access function is a **member function that only reads or display data** - it doesn't modify the object's internal data member.. and it's mainly used to:
    1. allow controlled read-only access to private data members check it state without breaking the encapsulation (getters or print functions)
    2. another type of access function return true or false depend on a condition these are called **predicate functions**
```c++
bool isAM() const { return hour < 12; }
bool isPM() const { return hour >= 12; }

if (time.isAM())
    std::cout << "Good morning!\n";

```
- Utility functions (helper functions) a private member function that performs a suporting task used by one or more of the class's public functions
    - they aren't meant to be called directly be class's users - only by other member functions inside the class .
    - purpose : to avoid code duplicate, organize code logically , to make public function simple

## 9.6 Time Class Case Study: Constructors with Default Arguments
- this section will by our second project in the chapter , you'll find it in folder named: **TIMEbyCONSTRUCTOR**
- this example show how we can simplify object creation by giving the constructor default arguments - like other functions do
- a constructor that deafults all its arguments is also a default constructor because it can be invoked with no aguments.
- there can be at most one default constructor per class
- setters and getters are the only functions that uses alot in the class itself and access the data member directly this to minimize the access to data this for good maintainability , if you change the internal representation of the data you only need to modify those functions rather change all functions

- don't repeat your code

### 9.2.6 Overloaded Constructors and C++11 Delegating Constructors

- constructor like normal functions can be overload - meaning a class can have multiple constructors with the same class name , but with different parameter lists
- its purpose is allow you to create object in different ways , depending on what information you have at certain time
- default arguments can handle overloaded constructor in one line, but use overloaded constructors when each version has different behavior
- you can use delegating constructors to call another constructor

```c++
Time::Time() : Time{0, 0, 0} {}
Time::Time(int hour) : Time{hour, 0, 0} {}
Time::Time(int hour, int minute) : Time{hour, minute, 0} {}
```
each of these delegates to the main constructor
```c++
Time::Time(int hour, int minute, int second)
```

- this help in avoid duplicate code

## 9.7 Destructors

- a special member function that automatically called when an object destroyed , it perform any necessary cleanup or termination tasks before the object's memory is reclaimed by the system.
- it has no parameter
- has no return type not even `void`
- cannot be overloaded, a class can have only one destructor
- it called implicitly when an object goes out of scope or is explicitly deleted
- its role is do termination housekeeping - any cleanup that should happen before the object is gone
- you need to define destructor yourself when:
    1. allocates dynamic memory using `new`
    2. manages resources like files, sockets
    3. needto release system handles before destruction

- when constructor and destructor call? it depend on : where object is defined (scope)? , when control enter and leaves that scope?

| Object Type                  | Constructor Call            | Destructor Call         | Notes                                       |
| ---------------------------- | --------------------------- | ----------------------- | ------------------------------------------- |
| **Global**                   | Before `main()` starts      | After `main()` ends     | Order across files not guaranteed           |
| **Local (non-static)**       | Each time scope is entered  | When scope ends         | Not destroyed if `exit()` or `abort()` used |
| **Static local**             | First time scope is entered | When program ends       | Persists between function calls             |
| **Dynamic (`new`/`delete`)** | When `new` runs             | When `delete` is called | Must be manually managed                    |



## 9.9 a Subtle Trap - returning a reference or pointer to a private data member

- the key idea:
    - in C++ a reference is an alias for an existing variable , if a member function returns a reference (or pointer) to a private data member, that means code outside the class can directly access and modify that private member - break encapsulation

```c++
int getHour() const { return hour; }  // safe, return a copy of hour , the user can use of modify the copy not the original data member

int& badSetHour(int h) {
    hour = h;
    return hour;  // returns a reference to private data , the actual data can be accessed now
}

t.badSetHour(20) = 30;  // modifies t.hour directly , because the reference can used as lvalue
```

- this break the encapsulation which says the private data only can be accessed and changed through well-defined interfaces (member functions) and those interfaces can check the validty of input
- if you really need to return a reference , return a const reference instead:
```c++
const int& getHour() const { return hour; } // the caller can read it , but not modify it
```

- the example in the book fig 9.11 - 9.13

## 9.10 Default Memberwise Assignment

- when you assign one object to another of the same class `date1 = date2` C++ performs default memberwise assignment, also called copy assignment which means:
    - Each data member in date1 is copied individually into the corresponding data member of date2
```c++
date2.month = date1.month
date2.day = date1.day
date2.year = date1.year
```
- Default memberwise assignment can cause serious problems when the class contains **pointers to dynamically allocated memory.**

```c++
class Student {
private:
    char* name;
};

student2 = student1; // will make both objects point to the same memory
```
- Then when one object is destroyed, the memory is freed — and the other object is left with a dangling pointer, leading to undefined behavior

## 9.11 const Objects and const Member Functions

- it help in appplying the principle of least privilege : give each part of your program only the access it truly needs.
- in c++ some object should be modifiable others should be read-only
- const object call only const member functions


## 9.12 Composition - objects as members of classes

- What is composition ?
    - it means a class has other objects of different classes as its data members (has-a relationship)

```c++
class AlarmClock {
private:
    Time alarmTime;   // AlarmClock "has-a" Time object
};
```
- this different from inheritance (an is-a relationship)
- even use string consider composition whereas string is a class in c++ not a primitive data type.
- this part have a project will named **EMPLOYEE**
- when constructing employee , we need to initialize both date and string members , this done via member initializer list
- each member is initialized directly by calling its own constructor
- note that Date class didn't define a constructor that takes anoher Date object, yet in employee we wrote , `birthDate{dateOfBirth}` passing a Date object , but it work well because every class gets a default copy constructor automatically, which does a memberwise copy of the object

## 9.13 Friend functions
- if we in a situation that we need a function outside of the class , but in the same time it need to access a private data member of that class , we then use friend functions

```c++
class Count {
    friend void setX(Count&, int);  // <-- this is the friend declaration
public:
    int getX() const { return x; }

private:
    int x{0};
};

// Friend function definition (outside the class)
void setX(Count& c, int val) {
    c.x = val;  // allowed because setX is a friend
}
```

```c++
class Count {
    friend void setX(Count&, int);  // <-- this is the friend declaration
public:
    int getX() const { return x; }

private:
    int x{0};
};

// Friend function definition (outside the class)
void setX(Count& c, int val) {
    c.x = val;  // allowed because setX is a friend
}
```
- friendship , is granted not taken : the class must explicitly declare who its firends are
- friendship isn't symmetric or transitive
- you can specify a friend class , that give all member functions of another class access

## 9.14 This pointer

- Every non-static member function of a class automatically receives a hidden pointer parameter called `this`.
- this points to the object that the function is currently acting on

```c++
Time t1, t2;
t1.setHour(5);
t2.setHour(10);
```
- When `t1.setHour(5)` runs → inside the function, this points to `t1`.
- it uses to avoid name conflicts

```c++
class Time {
private:
    int hour{0};

public:
    void setHour(int hour) {
        // 'hour' refers to the parameter, not the member
        this->hour = hour;  // explicitly assign to the object's data member
    }
};
```
- also used in cascaded Function calls `t.setHour(18).setMinute(30).setSecond(22);` how??
```c++
class Time {
public:
    Time& setHour(int h) {
        hour = h;
        return *this; // returns a reference to the current object
    }

    Time& setMinute(int m) {
        minute = m;
        return *this;
    }

    Time& setSecond(int s) {
        second = s;
        return *this;
    }
};
```
- Each setter returns *this (a reference to the current object)

## 9.15 Static class member
- Use static data members to save storage when a single copy of the data for all objects of a class will suffice.
- there's one copy of it
- it belongs to the class itself not a specific object
- static member functions:
    - can be called without any object
    - can access only static members
    - don't have a this pointer (since they don't act on specific object)
- to call it you have 2 options:
    - use the class name
    - use an object








