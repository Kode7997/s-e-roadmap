# MMAP - Memory Mapped file

Mapping of -
        [Files, Devices, Anonymous shared Memory, frame buffer (GPU), PIPE, Any resource with sequential data, HW registers] to the Process 
        virtual address space.

## Use-Cases

    a. Database Engines (SQLite, RocksDB)
        - Use mmap for page management
        - Zero-copy B-tree access

    b. Image/Video Processing
        - Process multi-GB files without loading entirely
        - Efficient tile-based access

    c. Search Engines (Lucene)
        - Memory-map index files
        - Instant relevance scoring

    d. Memory-mapped Queues
        - Inter-process communication
        - Shared data structures

    e. Sparse Files
        - Create huge files instantly
        - Only write accessed portions

## Why MMAP?

- It enables direct access to memory location avoiding kernel calls read(), write

- Before MMAP
        Every read maintains 2-copies of same data in a cycle.
        - a copy(buffer) at kernel space.
        - a copy(buffer) at above kernel to forward data to upstream or user-space

- With MMAP
        - It's a zero copy

- It improves the performance by 10-100x faster than tradition memory access.

## How does mmap work?

    Your Process Virtual Address:    Physical Memory:           Disk:
    ┌──────────────────────┐         ┌──────────┐              ┌─────────┐
    │ 0x7f0000000000 ──┐   │         │ Page 1   │              │File Byte│
    │ 0x7f0001000000 ──┼─┐ │         │ [4KB]    │◄─────────---─│ 0-4095  │
    │ 0x7f0002000000 ──┼─┼─┤────────►│ Page 2   │ (page fault) │         │
    │ ...              │ │ │         │ [4KB]    │◄──────────── │File Byte│
    │ 0x7f0001000fff ──┼─┤ │         │          │              │4096-    │
    └──────────────────┘ │ │         └──────────┘              │8191     │
            ▲            │ │             ▲                     └─────────┘
            │ Your       │ │             │
            │ Process    │ │             │
            │ Virtual    │ └─────────────┘
            │ Address    │    OS Page Tables
            │ Space      │    (translation)
            │            │
            └───────────-┘

    MMAP creates this translation(TLB which is L1 Cache). this page table is maintained per process in kernel memory space.
    Virtual Address in Process ────(via page table)──► Disk File Bytes

**Note:** malloc v/s mmap
    a. malloc internally uses brk/mmap to map to Physical RAM via virtual address
    b. mmap maps to FILE on disk via virtual address in page table

    Above two are different entries in the page table.
