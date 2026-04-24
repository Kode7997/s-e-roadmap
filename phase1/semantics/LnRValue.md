# LValue and RValue

## Flow of Content

1. Core concepts (lvalue, rvalue)
2. References (lvalue ref, rvalue ref)
3. Decision flowchart
4. Applications of lvalue and rvalue
5. Reference v/s pointer (off topic)

### 1. lvalue and rvalue

lvalue - expression that has memory location
rvalue - expression that is temporary and doesn't have memory location

e.g:
    lvalue

```cpp

int x = 10;
std::String s = "hello"
std::vector<int> vec = {1,2,3,4}; 

```

rvalue

```cpp
    x++; // rvalue
    x+3; // rvalue
    5;   // rvalue
```

### 2. lvaue reference and rvalue reference

lvalue referece (T&): Binds to lvalues ONLY with 1 exception
e.g:

```cpp
// y is a lvalue reference
int x = 10;
int& y = x; // y is alias of x. therefore changes to 'y' also changes 'x' 
y = 20;     // x is also 20.
```

**use-case**: pass by reference. this avoids copy the whole content.

```cpp
void process(int& var){}

int x = 10;
process(x);
```

Bind values to lvalue and rvalue

```cpp
int x = 10;
int& lref = x;  // can bind lvalue to lvalue reference
int& rref = 5   // X wrong!! cannot bind rvalue to lvalue reference however as follows
const int& rref2 = 5    // Allowed. can bind rvalue to const lvalue reference
```

rvalue reference (T&&) - Binds to rvalues ONLY
e.g:

```cpp
int x = 5;
int&& rref = x;        // ERROR: rvalue ref can't bind to lvalue
int&& rref2 = 5;       // OK: rvalue ref binds to rvalue

std::vector<int>&& vec_rref = std::vector<int>{1, 2, 3};  // Allowed

std::string str = "hello";
std::string&& str_rref = str;   //ERROR: rvalue reference cannot bind to lvalue
std::string&& str_rref2 = std::string("temp");  // Allowed, since std::string is on right of expression and temp string
```

**use-case**: It is used to steal the resource. avoid copying.
**NOTE**: std::move(lvalue) -- converts lvalue to rvalue and can be assigned to rvalue reference. improves performance and 
        allows less utilization of memory. move is faster than copy

e.g:

```cpp
int x = 10;
int&& rref = std::move(x); // x becomes invalid and using of x after this exp will lead to UB
```

### 3. Decision flow chart

    Is the object a temporary (rvalue)?
    │
    ├─ YES → Can use rvalue reference (T&&)
    │        └─ Move semantics: steal resources
    │           Example: MyClass(MyClass&& other) { ... }
    │
    └─ NO (lvalue) → Use lvalue reference (const T&) or copy
                    └─ Copy semantics: deep copy
                        Example: MyClass(const MyClass& other) { ... }

### 4. Applications of lvalue and rlvalue

#### Key Insight Summary

| Operation | Method | Time | Example |
|---|---|---|---|
| Copy Constructor | Allocate + Copy each element | O(n) | new + memcpy |
| Move Constructor | Steal pointer, invalidate source | O(1) | Just pointer swap |
| Copy Assignment | Delete old + Allocate + Copy | O(n) | delete[] + new + memcpy |
| Move Assignment | Delete old + Steal pointer | O(1) | delete[] + pointer swap |

### 5. Reference v/s Pointer

* Reference and Pointers are not the same.
* reference cannot be null but pointer can be nullptr
* Under-hood compiler convert reference to pointers and performs operation but semantically in cpp reference is alias to object.
