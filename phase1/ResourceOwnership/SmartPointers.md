# Smart Pointers

## Unique Pointer

    std::unique_ptr<R>
    std::make_unique<R>()

## Shared Pointer

    std::shared_ptr<R>
    std::make_shared<R>()

## Weak Pointer

    It is used along shared pointer if there is any cyclicity. usually trees, graphs, circular linkedlist
    std::weak_ptr<R>

## Special Cases

1. If raw pointers needed from smart pointers use .get() method.
2. Transfer ownership - use std::move(R);
3. ArrayAllocation - use unique pointer<T[]>
4. Polymorphism - use smart_pointer<Base>.
5. C API integration - use custom deletor.
