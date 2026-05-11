# 🏗️ ~14-Month Systems Engineering Roadmap

**Target:** Systems Engineer (Qualcomm / NVIDIA / AMD)  
**Core Stack:** C++ · Linux · Concurrency · Hardware Architecture · Low-Level System Design  
**Original Start Date:** 2026-02-11  
**Timeline Reset:** 2026-04-17 (Phase 1 partially complete — RAII, smart pointers, memory layout, move semantics done)  
**Realistic End Date:** ~June 2027  

---

## The Full System Stack (Reference Model)

```
┌──────────────────────────────────────────────────────────────────┐
│                        APPLICATION                               │
│  User-space services, frameworks, inference pipelines            │
├──────────────────────────────────────────────────────────────────┤
│                    RUNTIME / LIBRARIES                            │
│  libc, libstdc++, CUDA Runtime, TensorRT, DPDK, allocators       │
├──────────────────────────────────────────────────────────────────┤
│                         KERNEL                                    │
│  Scheduler, VFS, memory manager, network stack, cgroups           │
├──────────────────────────────────────────────────────────────────┤
│                         DRIVER                                    │
│  GPU drivers, NIC drivers, storage drivers, DMA engines           │
├──────────────────────────────────────────────────────────────────┤
│                        FIRMWARE                                   │
│  BIOS/UEFI, microcontroller FW, GPU microcode, NIC firmware       │
├──────────────────────────────────────────────────────────────────┤
│                   HARDWARE (Silicon)                              │
│  CPU/GPU cores, caches (L1/L2/L3), DMA engines,                  │
│  PCIe/CXL interconnect, DRAM controllers, NPUs/TPUs              │
└──────────────────────────────────────────────────────────────────┘
```

<!--
==========================================================================
COMMENTED OUT: AI Agents Across the Stack — Interlinking Architecture
REASON: Aspirational fantasy. None of this exists in production at target
companies in the way depicted. The multi-agent orchestrator concept, firmware
agents, hardware agents — not how Qualcomm/NVIDIA/AMD actually work.
Replaced with practical AI/ML integration skills in Phase 6B (2 weeks).

Original content preserved in ROADMAP_old.md if needed for reference.
==========================================================================
-->

---

## 📊 Skill Matrix & Target Company Coverage

| Skill Area | Qualcomm Needs | NVIDIA Needs | AMD Needs | Covered In |
|-----------|---------------|-------------|----------|-----------|
| C++ (modern, systems) | ✅ Critical | ✅ Critical | ✅ Critical | Phase 1 |
| ARM architecture | ✅ Critical | ⚠️ Nice to have | ⚠️ Nice to have | Phase 4 |
| CUDA/GPU compute | ⚠️ Some roles | ✅ Critical | ✅ Critical (HIP) | Phase 4 |
| Linux kernel/OS | ✅ Critical | ✅ Important | ✅ Important | Phase 2 |
| Concurrency/atomics | ✅ Critical | ✅ Critical | ✅ Critical | Phase 3 |
| Lock-free algorithms | ✅ Important | ✅ Important | ✅ Important | Phase 3, 6 |
| Cache/memory perf | ✅ Critical | ✅ Critical | ✅ Critical | Phase 4 |
| DMA/PCIe | ✅ Critical | ✅ Important | ✅ Important | Phase 4 |
| **Low-level system design** | ✅ Critical | ✅ Critical | ✅ Critical | **Phase 5 (NEW)** |
| **Linker/loader/ELF** | ✅ Important | ✅ Important | ✅ Important | **Phase 2 (NEW)** |
| **IPC mechanisms** | ✅ Critical | ✅ Important | ✅ Important | **Phase 2 (NEW)** |
| **Debugging (GDB, core dumps)** | ✅ Critical | ✅ Critical | ✅ Critical | **Phase 2 (NEW)** |
| **RTOS / embedded basics** | ✅ Critical | ⚠️ Some roles | ⚠️ Some roles | **Phase 4 (NEW)** |
| AI/ML integration (practical) | ⚠️ Growing | ✅ Important | ✅ Important | Phase 6B |
| eBPF/tracing | ⚠️ Nice to have | ⚠️ Nice to have | ⚠️ Nice to have | Phase 4 (1 week) |
| Technical leadership | ✅ Required | ✅ Required | ✅ Required | Phase 7 |
| Design docs/RFCs | ✅ Required | ✅ Required | ✅ Required | Every phase |

---

## Phase 0: Environment, Toolchain & Mindset (DONE — Week 0–1)

**Goal:** Production-grade dev environment. System-layer thinking from day one.

### Setup

```bash
# Ubuntu 22.04 / Fedora 38+
sudo apt install gcc g++ clang clang-tools cmake ninja-build \
  gdb lldb valgrind linux-tools-common linux-tools-generic \
  git docker.io python3 python3-pip

# Sanitizers (built into GCC/Clang — verify)
# ASan, TSan, UBSan, MSan

# Cross-compilation (ARM)
sudo apt install gcc-aarch64-linux-gnu g++-aarch64-linux-gnu qemu-user

# GPU (if NVIDIA GPU available)
# Install CUDA toolkit + nvcc

# Profiling
sudo apt install linux-perf hotspot flamegraph
```

### Deliverables

- [x] CMakeLists.txt template with ASan/TSan/UBSan toggles, cross-compile target, benchmark target
- [x] Stack diagram printed/pinned to wall
- [x] All tools installed and verified

### Mindset (ongoing forever)

```
Every bug          → "Which layer? CPU / cache / OS / memory / my code?"
Every optimization → "Where is the bottleneck? Measure first."
Every API          → "Who owns this resource? What is the lifetime?"
Every struct       → "What is the memory layout? Padding? Cache line?"
```

---

## Phase 1: C++ as a Systems Language (Month 1–3)

**Timeline:** Feb 11 – May 15, 2026 (~13 weeks)  
**Status as of Apr 17:** Weeks 1-3, 5 substantially done. Weeks 4, 6-10 remaining (~4 weeks).  
**Goal:** Master C++ ownership, lifetime, layout, and zero-cost abstractions. NO concurrency yet.

### Month 1: Memory, Ownership, Layout (MOSTLY DONE)

| Week | Topic | Status | Deliverable |
|------|-------|--------|-------------|
| 1 | Stack vs heap, RAII, destructor semantics, rule of 5 | ✅ Done | RAII wrappers for FILE*, socket, mmap |
| 2 | Smart pointers (unique_ptr, shared_ptr, weak_ptr), custom deleters | ✅ Done | Refactor a raw-pointer codebase to smart pointers |
| 3 | Memory layout: sizeof, alignof, offsetof, padding, cache lines | ✅ Done | Tool that prints struct layout + padding |

### Month 2: Move Semantics, Allocators Deep-Dive

| Week | Topic | Deliverable |
|------|-------|-------------|
| 4 | Rvalue refs, std::move, move ctors/assignment, noexcept | ✅ Done — Benchmark: copy vs move for 1M objects |
| 5 | Allocators part 1: placement new, memory pools, arena allocators | Implement a fixed-size memory pool allocator |
| 6 | Allocators part 2: slab allocator concept, jemalloc/tcmalloc internals study, fragmentation strategies | Benchmark your pool allocator vs glibc malloc. Write analysis of jemalloc's arena design. |
| 7 | Allocators part 3: custom allocator for STL containers, aligned allocation | `PoolAllocator<T>` — fixed-block with RAII, move semantics, alignment control, STL-compatible |

> **Why 3 weeks on allocators:** Allocator design is a top interview topic at all three target companies. jemalloc/tcmalloc internals, SLAB allocator (kernel), thread-local caches — these come up constantly. 1 week was too shallow.

### Month 3 (remaining): Templates, Compile-Time

| Week | Topic | Deliverable |
|------|-------|-------------|
| 8 | Perfect forwarding, universal references, std::forward | Implement `make_unique` from scratch |
| 9 | Templates: specialization, SFINAE, type_traits, concepts (C++20) | Implement `Optional<T>` supporting move-only types |
| 10 | Compile-time: constexpr, consteval, template metaprogramming | Compile-time hash map or type-safe unit system |

### Mini-Projects

1. `PoolAllocator<T>` — fixed-block allocator with RAII, move semantics, alignment control, STL-compatible
2. `Optional<T>` — supports move-only types, emplacement, strong exception safety
3. Struct layout analyzer — prints field offsets, padding bytes, total size, cache-line crossings

### Acceptance Criteria

- [ ] Zero leaks (Valgrind clean)
- [ ] Move constructors are `noexcept`
- [ ] APIs express ownership clearly in signatures
- [ ] Templates give clear compile-time errors (concepts or static_assert)
- [ ] Benchmarks show move >> copy for non-trivial types
- [ ] Allocator benchmarked against glibc malloc with analysis
- [ ] Design doc: 1-page writeup of allocator design decisions

### Resources

- *Effective Modern C++* — Scott Meyers
- cppreference.com
- Compiler Explorer (godbolt.org) for assembly inspection
- jemalloc source code + design doc (Facebook engineering blog)

---

## Phase 2: Linux / OS Internals (Month 4–6)

**Timeline:** May 15 – Aug 1, 2026 (~11 weeks)  
**Goal:** Understand how C++ code maps to OS primitives. Process model, virtual memory, I/O, IPC, linker, debugging.

### Month 4: Processes, Memory, Signals

| Week | Topic | Deliverable |
|------|-------|-------------|
| 11 | Process model: fork, exec, wait, PID, file descriptor table | Mini shell that forks+execs commands |
| 12 | Virtual memory: pages, page tables, TLB, mmap, mprotect | Program that maps files, measures page fault cost |
| 13 | Heap internals: malloc/free, sbrk, mmap threshold, fragmentation | Custom malloc benchmarked vs glibc |
| 14 | Signals, signal handlers, async-signal-safety | Signal-safe logging daemon |

### Month 5: I/O, Networking, IPC

| Week | Topic | Deliverable |
|------|-------|-------------|
| 15 | File descriptors, read/write, buffered vs unbuffered I/O | High-throughput file copier (compare buffered vs mmap vs direct I/O) |
| 16 | Sockets: TCP/UDP, bind/listen/accept, non-blocking I/O | Echo server (blocking + non-blocking versions) |
| 17 | Event-driven I/O: select → poll → epoll, edge vs level triggered | epoll-based multi-client server |
| 18 | **IPC mechanisms: shared memory, message queues, pipes, Unix domain sockets** | **IPC benchmark: compare latency/throughput of shm vs pipe vs Unix socket vs TCP loopback** |

> **NEW — Week 18 (IPC):** Shared memory + semaphores, POSIX message queues, pipe/FIFO, Unix domain sockets. These are the building blocks of every systems design at Qualcomm/NVIDIA. Missing this is a gap.

### Month 6 (first 3 weeks): Linker, Debugging, Profiling

| Week | Topic | Deliverable |
|------|-------|-------------|
| 19 | **Linker/Loader/ELF: ELF format, dynamic linking, symbol resolution, PLT/GOT, LD_PRELOAD, linker scripts** | **Write an LD_PRELOAD malloc interceptor. Diagram ELF loading. Inspect PLT/GOT with readelf/objdump.** |
| 20 | **Debugging mastery: GDB/LLDB scripting, core dump analysis, reverse debugging (rr), post-mortem debugging** | **Debug a provided crashing binary using only GDB + core dump. Write GDB python script for custom pretty-printer.** |
| 21 | Profiling: perf, ftrace, strace, Valgrind, ASan/TSan | Profile all previous projects, write perf reports |

> **NEW — Week 19 (Linker/ELF):** Dynamic linking, symbol resolution, PLT/GOT — critical for understanding how software actually loads and runs. Comes up in driver and systems roles constantly.
>
> **NEW — Week 20 (Debugging):** GDB/LLDB mastery is a daily skill. Core dump analysis is how you debug production crashes at these companies. Not having this is an immediate red flag.

### Compiler & ABI Internals (overlap with Week 19–21)

- vtable layout, virtual dispatch cost measurement
- Calling conventions (System V AMD64 ABI)
- Name mangling, `extern "C"`
- LTO (Link-Time Optimization) and its impact on inlining

### Mini-Projects

1. **Multi-client chat server** — epoll-based, non-blocking, with clean resource management (RAII for fds)
2. **Memory profiler** — tracks mmap/munmap calls via LD_PRELOAD, reports allocation hot-spots
3. **IPC latency benchmark suite** — compare all IPC mechanisms with statistical analysis

### Acceptance Criteria

- [ ] Chat server handles 1000+ concurrent connections
- [ ] perf report identifies and explains top 3 hotspots
- [ ] mmap-based file I/O benchmarked and compared with explanation
- [ ] IPC benchmark with latency percentiles (p50, p99, p999) for each mechanism
- [ ] Can analyze a core dump and identify root cause using GDB
- [ ] Can explain ELF loading, PLT/GOT, symbol resolution
- [ ] Design doc: virtual memory layout diagram for your programs

### Resources

- *The Linux Programming Interface* — Michael Kerrisk
- *Understanding the Linux Kernel* — Bovet & Cesati
- *Linkers & Loaders* — John R. Levine (or Ian Lance Taylor's "Linkers" blog series)
- `man 7 signal`, `man 2 mmap`, `man 7 epoll`
- GDB documentation + rr (reverse debugger)

---

## Phase 3: Concurrency & Atomics (Month 7–9)

**Timeline:** Aug 1 – Oct 10, 2026 (~10 weeks)  
**Goal:** From mutexes to lock-free. This is where Qualcomm/NVIDIA/AMD interviews focus heavily.

> **Why 10 weeks instead of 8:** Lock-free programming is genuinely hard. The original plan crammed SPSC ring buffer + MPMC queue design into 2 weeks. You need time to get these right and stress-tested, not just "implemented."

### Month 7: Threading Fundamentals & Synchronization

| Week | Topic | Deliverable |
|------|-------|-------------|
| 22 | std::thread, std::jthread, thread lifecycle, join/detach | Thread pool (fixed-size, task queue) |
| 23 | Mutexes: std::mutex, lock_guard, unique_lock, deadlock avoidance | Dining philosophers (multiple solutions) |
| 24 | Condition variables, semaphores, barriers, latches (C++20) | Bounded producer-consumer queue |
| 25 | **Real-time scheduling: priority inversion, priority inheritance, RT policies (SCHED_FIFO, SCHED_RR)** | **Demonstrate priority inversion + fix with priority inheritance mutex. Measure scheduling jitter under RT vs CFS.** |

> **NEW — Week 25 (RT scheduling):** Qualcomm especially cares about real-time. Priority inversion is a classic interview topic. SCHED_FIFO/SCHED_RR, CPU affinity, and deterministic latency matter for driver and firmware-adjacent work.

### Month 8: Atomics, Memory Model & Lock-Free

| Week | Topic | Deliverable |
|------|-------|-------------|
| 26 | Thread safety analysis: TSan, race detection, happens-before | Annotate and fix races in a given buggy codebase |
| 27 | std::atomic: load/store/exchange/CAS, lock-free property | Atomic counter, spinlock implementation |
| 28 | Memory ordering: seq_cst, acquire/release, relaxed, fences | Programs demonstrating ordering differences |
| 29 | Lock-free SPSC ring buffer — design + implement | Cache-line aligned, templated, initial stress test |

### Month 9 (first 2 weeks): Lock-Free Hardening

| Week | Topic | Deliverable |
|------|-------|-------------|
| 30 | SPSC ring buffer — stress test, benchmark, fix edge cases | Full stress test (10M ops, 2 threads, 10 min). Benchmark vs mutex queue. |
| 31 | Lock-free MPMC queue design: ABA problem, hazard pointers, epoch-based reclamation | Detailed design doc for MPMC queue (implement in Phase 6) |

### Mini-Projects

1. **Thread pool with work-stealing** — move-only task type, RAII lifetime, benchmarked
2. **SPSC lock-free ring buffer** — cache-line aligned, templated, stress-tested, benchmarked

### Acceptance Criteria

- [ ] SPSC ring: zero lost items under 10M ops stress test (2 threads, 10 min)
- [ ] Thread pool: handles 100K tasks, benchmark against `std::async`
- [ ] Memory orderings documented with "why" for each choice
- [ ] TSan clean on all concurrency code
- [ ] Can explain and demonstrate priority inversion
- [ ] Design doc: memory ordering diagram for SPSC ring buffer

### Resources

- *C++ Concurrency in Action* — Anthony Williams
- Jeff Preshing's blog on lock-free programming
- CppCon talks on atomics (Herb Sutter, Fedor Pikus)
- Linux RT wiki (rt.wiki.kernel.org)

---

## Phase 4: Hardware Architecture & GPU Compute (Month 9–12)

**Timeline:** Oct 10, 2026 – Jan 15, 2027 (~14 weeks)  
**Goal:** Understand what happens below the OS. CPU microarchitecture, caches, GPU compute, embedded basics.

> **Why 14 weeks instead of 8:** The original plan tried to cover CPU architecture + CUDA from scratch + HIP porting + DMA/PCIe in 8 weeks. CUDA alone takes 5-6 weeks to be productive. This was the most unrealistic phase.

### Month 9–10: CPU Architecture & Cache Effects (5 weeks)

| Week | Topic | Deliverable |
|------|-------|-------------|
| 32 | CPU pipeline: fetch, decode, execute, retire; branch prediction | Benchmark: sorted vs unsorted array (branch prediction demo) |
| 33 | Cache hierarchy: L1/L2/L3, cache lines, associativity, MESI protocol | Array traversal benchmark: row-major vs column-major |
| 34 | False sharing, cache-line padding, NUMA topology | Fix false sharing in a multi-threaded counter benchmark |
| 35 | x86 vs ARM: memory models (TSO vs weak), ISA differences | Cross-compile a benchmark to ARM, compare behavior |
| 36 | **RTOS & embedded basics: FreeRTOS concepts, memory-mapped I/O, interrupt service routines, bare-metal thinking** | **Read FreeRTOS source for task scheduler. Write a bare-metal style program with MMIO simulation. Understand ISR constraints.** |

> **NEW — Week 36 (RTOS/embedded):** All three target companies have significant embedded work. Qualcomm especially. Understanding RTOS task scheduling, MMIO, ISR constraints, and the difference between RTOS and Linux scheduling is expected knowledge.

### Month 10–12: GPU Compute & Heterogeneous Systems (6 weeks)

| Week | Topic | Deliverable |
|------|-------|-------------|
| 37 | GPU architecture: warps/wavefronts, SIMT, memory hierarchy, occupancy | Diagram: GPU vs CPU execution model. Study occupancy calculator. |
| 38 | CUDA basics: kernel launch, threadIdx, blockIdx, grid/block dimensions | Vector add, reduction kernel. Understand launch configuration. |
| 39 | CUDA shared memory, bank conflicts, tiling strategies | Matrix multiply: naive → shared memory → tiled. Profile with nvprof/Nsight. |
| 40 | CUDA streams, events, async execution, error handling | Overlap compute+transfer benchmark with streams |
| 41 | HIP (AMD) / CUDA portability | Port CUDA matrix multiply to HIP. Understand hipify tool. |
| 42 | DMA, PCIe, host↔device transfers, pinned memory, unified memory | Benchmark: pageable vs pinned vs unified memory transfer |

### eBPF (1 week awareness — Week 43)

| Week | Topic | Deliverable |
|------|-------|-------------|
| 43 | eBPF basics: write a simple tracing program, understand BPF verifier | Trace syscalls for one of your previous projects. 1-page writeup on what eBPF enables. |

> **Trimmed:** eBPF was originally threaded across multiple areas. For your target roles, 1 week of awareness is sufficient. You'll use internal profiling tools at these companies, not write eBPF programs day-to-day.

### Additional study during Phase 4 (overlap reading)

- DMA engine concepts, scatter-gather lists
- PCIe BAR mapping, MMIO from userspace
- Memory-mapped device registers

### Mini-Projects

1. **Cache-aware matrix multiply** — benchmark naive vs blocked vs SIMD-hinted, analyze with perf
2. **GPU matrix multiply** — CUDA + HIP versions, profile with nvprof/rocprof
3. **False sharing eliminator** — tool that detects and fixes false sharing in given code

### Acceptance Criteria

- [ ] Can explain MESI protocol and demonstrate false sharing with numbers
- [ ] CUDA matrix multiply profiled with nvprof, identify bottlenecks
- [ ] Cross-compiled ARM binary runs correctly under QEMU
- [ ] perf stat report with IPC, cache miss %, branch miss % for all benchmarks
- [ ] Can explain difference between RTOS scheduling and Linux CFS
- [ ] Can explain warp divergence, bank conflicts, occupancy
- [ ] Design doc: CPU vs GPU execution model comparison

### Resources

- *Computer Systems: A Programmer's Perspective* — Bryant & O'Hallaron
- Intel/ARM architecture manuals
- NVIDIA CUDA Programming Guide
- AMD HIP Programming Guide
- *Making Embedded Systems* — Elecia White (skim for RTOS chapters)
- FreeRTOS source code (tasks.c, queue.c)

---

## Phase 5: Low-Level System Design (Month 12–13) — NEW

**Timeline:** Jan 15 – Feb 15, 2027 (~4 weeks)  
**Goal:** Practice hardware-software co-design and low-level system design. This is the #1 missing skill for staff-level systems roles.

> **Why this phase exists:** System design at Qualcomm/NVIDIA/AMD is NOT web-scale system design (no load balancers, no microservices, no database sharding). It's: "Design the software stack for this hardware block." "Design a memory allocator for this use case." "Design the interrupt handling scheme for this device." The original roadmap had zero practice for this.

### Weekly Breakdown

| Week | Design Problem | Deliverable |
|------|---------------|-------------|
| 44 | **Design a memory allocator system**: thread-local caches, size-class segregation, mmap backend, fragmentation strategy. Consider: embedded constraints vs server workloads. | 3-page design doc with diagrams. Trade-offs section comparing your design vs jemalloc/tcmalloc. |
| 45 | **Design a device driver framework**: register abstraction, interrupt handling, DMA buffer management, power state transitions, error recovery. | 3-page design doc. Include: state machine for power management, interrupt handler → deferred work flow. |
| 46 | **Design a high-throughput logging system**: lock-free log buffer, async flush, structured vs unstructured, crash safety, log rotation, backpressure. | 3-page design doc + prototype implementation of the lock-free log buffer core. |
| 47 | **Hardware-software co-design exercise**: Given a block diagram of a DMA engine with N channels, design the software driver. Address: descriptor ring management, completion handling, error recovery, multi-client arbitration. | 3-page design doc. This is the exact type of interview question at Qualcomm/NVIDIA. |

### Practice Format

For each design problem:
1. **Requirements clarification** (5 min) — what are the constraints?
2. **High-level architecture** (10 min) — block diagram, data flow
3. **Detailed design** (30 min) — data structures, APIs, memory layout, threading model
4. **Trade-offs & alternatives** (10 min) — what you chose and why
5. **Write it up** (60 min) — clean design doc with diagrams

### Acceptance Criteria

- [ ] 4 design docs, each 3-5 pages with architecture diagrams
- [ ] Every doc has a "Trade-offs & Alternatives" section
- [ ] At least 2 designs include memory layout diagrams
- [ ] At least 1 design includes a state machine diagram
- [ ] Can walk through any design verbally in 15 minutes

### Resources

- Linux kernel source: `drivers/dma/`, `mm/slab.c`, `kernel/printk/`
- Design docs from open-source projects (DPDK, SPDK)

---

## Phase 6: Cross-Layer Integration Projects (Month 13–15)

**Timeline:** Feb 15 – Apr 25, 2027 (~10 weeks)  
**Goal:** Architect-level projects that span multiple layers. This is your portfolio.

### Project A: High-Performance Packet Processor (Primary — 5 weeks)

```
                     ┌──────────────┐
      NIC (raw sock) │  CAPTURE     │ epoll + mmap'd ring buffer
      ───────────────►  THREAD      │
                     └──────┬───────┘
                            │ lock-free SPSC ring
                     ┌──────▼───────┐
                     │  PARSE       │ zero-copy packet parsing
                     │  THREAD(s)   │ thread-pinned, NUMA-aware
                     └──────┬───────┘
                            │ lock-free MPMC queue
                     ┌──────▼───────┐
                     │  PROCESS     │ filtering, stats, forwarding
                     │  THREAD(s)   │ SIMD-optimized where possible
                     └──────┬───────┘
                            │
                     ┌──────▼───────┐
                     │  STATS /     │ atomic counters, per-thread
                     │  OUTPUT      │ cache-line aligned
                     └──────────────┘
```

**Demonstrates:** epoll I/O, lock-free queues, NUMA awareness, cache optimization, RAII resource management, move semantics, templates, profiling.

<!--
==========================================================================
COMMENTED OUT: Project B — AI-Assisted Performance Profiler
REASON: Scope creep. Combining eBPF + ML classification + C++/Python interop
+ lock-free transport is 3 projects mashed into one. The ML classification
part adds marginal portfolio value for systems roles. At these companies
you'll use internal profiling tools (VTune, Nsight, internal perf infra),
not build your own ML profiler.

Better use of this time: Lock-Free MPMC Queue (hard data structure that
directly demonstrates concurrency expertise) + practical AI/ML integration.

Original Project B content preserved in ROADMAP_old.md.
==========================================================================
-->

### Project B: Lock-Free MPMC Queue (Hard Data Structure — 3 weeks)

- Full hazard-pointer or epoch-based reclamation
- Templated, allocator-aware, cache-line padded
- Stress tested with 8+ producer/consumer threads
- Benchmarked against `moodycamel::ConcurrentQueue` and `boost::lockfree::queue`

**Demonstrates:** Deep concurrency expertise, memory reclamation, ABA problem handling, performance engineering.

### Phase 6B: Practical AI/ML Integration (2 weeks)

> **What actually matters for systems roles at these companies:**
> - NVIDIA: CUDA kernel optimization for ML ops, TensorRT C++ API, model serving infra
> - Qualcomm: ONNX Runtime / TFLite on-device, NPU/DSP dispatch, quantization effects
> - AMD: ROCm/MIOpen, HIP kernel optimization, ML compiler awareness (MLIR)
>
> **What does NOT matter:** Building ML models, training pipelines, "AI agents"

| Week | Topic | Deliverable |
|------|-------|-------------|
| 48 | C++ inference integration: load an ONNX model using ONNX Runtime C++ API. Understand: model loading, session creation, input/output tensor handling, inference execution. | Working C++ program that loads a pre-trained model and runs inference. Benchmark inference latency. |
| 49 | Quantization awareness + ML compiler basics: INT8 vs FP16 vs FP32 trade-offs, operator fusion concept, TVM/XLA/MLIR at awareness level. TensorRT basic usage (if NVIDIA GPU available). | 1-page writeup: "How ML models get from Python training to C++ inference in production." Quantized vs full-precision inference benchmark. |

### Deliverables for each project

- [ ] Working code with CI (GitHub Actions: GCC + Clang, ASan + TSan)
- [ ] Design doc (3–5 pages): architecture, memory ordering rationale, trade-offs
- [ ] Benchmark report with graphs
- [ ] Profiling report (perf, cachegrind, or nvprof)
- [ ] README with build instructions and usage

---

## Phase 7: Interview Readiness & Technical Leadership (Month 15–16)

**Timeline:** Apr 25 – Jun 10, 2027 (~6 weeks)  
**Goal:** Staff-level readiness. Technical depth + leadership signal.

### Technical Interview Prep (starts Phase 2, intensifies here)

**Weekly cadence from Phase 2 onward:**

- 2 LeetCode medium/hard (concurrency, systems, bit manipulation)
- 1 system design problem per week (low-level, NOT web-scale)
- 1 "explain to me" verbal drill

**Final 6 weeks intensive focus areas:**

| Focus Area | Practice |
|-----------|---------|
| C++ deep | "Implement shared_ptr", "What does noexcept affect?", "Explain vtable layout", "How does dynamic linking work?" |
| Concurrency | "Design a thread-safe LRU cache", "Implement read-write lock", "Explain ABA", "What is priority inversion?" |
| Systems | "What happens when you call malloc?", "Explain page fault handling", "Design epoll", "Compare IPC mechanisms" |
| Architecture | "x86 vs ARM memory model", "Explain cache coherence", "What is false sharing?", "Explain DMA" |
| GPU | "Explain warp divergence", "CUDA shared memory bank conflicts", "Host↔device transfer optimization" |
| **System design** | **"Design a memory allocator", "Design a DMA engine driver", "Design a lock-free logging system", "Design a GPU command scheduler"** |

### Staff-Level Leadership Skills

| Skill | How to demonstrate |
|-------|--------------------|
| **Technical vision** | Write a 2-page RFC for each Phase 6 project before coding |
| **Mentoring** | Publish projects on GitHub with detailed READMEs; write blog posts |
| **Code review** | Review open-source PRs (DPDK, LLVM, Linux kernel) |
| **Cross-team influence** | Document how projects span layers; show systems thinking |
| **Trade-off articulation** | Every design doc must have a "Trade-offs & Alternatives" section |

---

## Phase 8: Positioning & Networking (Ongoing from Month 1)

| Month | Action |
|-------|--------|
| 1–3 | Set up GitHub portfolio repo structure. Start a dev blog. |
| 4–6 | First open-source contribution (DPDK/LLVM/Linux documentation or small bug). |
| 7–9 | LinkedIn: post about concurrency learnings with benchmarks. Connect with target company engineers. |
| 10–12 | Submit a talk proposal to a local meetup or CppCon/CppIndia. |
| 13–14 | Portfolio projects polished with READMEs, benchmarks, design docs. |
| 15–16 | Apply. Reach out to recruiters/referrals. Prepare portfolio walkthrough demo (15 min). |

### Resume Bullet Format (Staff-level)

```
• Designed and implemented a lock-free SPSC ring buffer achieving 
  50M ops/sec with zero data loss under TSan, reducing inter-thread 
  latency by 3.2x vs mutex-based queue (C++20, Linux, perf)

• Architected a multi-threaded packet processing pipeline handling 
  1Gbps throughput with NUMA-aware thread pinning and zero-copy 
  buffer management, profiled with perf and VTune

• Wrote 4 low-level system design docs covering memory allocator 
  architecture, DMA driver design, and lock-free logging — each with 
  trade-off analysis and memory layout diagrams
```

<!--
REMOVED: Resume bullet about "AI-assisted performance profiler with 92% accuracy"
— that project was cut. Don't claim things you didn't build.
-->

---

## 🔑 Key Principles

```
1. MEASURE BEFORE OPTIMIZE
   No claim without numbers. perf, cachegrind, nvprof, benchmarks.

2. LAYERS, NOT SILOS
   Every project must touch ≥2 layers. "I optimized the C++ code" is 
   junior. "I traced the bottleneck from userspace through the scheduler 
   to L3 cache contention" is staff.

3. OWNERSHIP OVER KNOWLEDGE
   Reading about atomics ≠ implementing a correct lock-free queue 
   that passes TSan. Build it, test it, break it, fix it.

4. WRITE IT DOWN
   Staff engineers write design docs, not just code. One design doc 
   per phase minimum.

5. DESIGN BEFORE CODE
   For any non-trivial system, write the design doc first. Identify 
   trade-offs before committing to an approach. This is what separates
   senior from staff.

6. PORTFOLIO > RESUME
   A GitHub repo with a benchmarked lock-free queue + design doc 
   beats 10 bullet points about "experience with concurrency."
```

---

## 📚 Complete Reading List

| Resource | Phase |
|----------|-------|
| *Effective Modern C++* — Scott Meyers | 1 |
| *C++ Concurrency in Action* — Anthony Williams | 3 |
| *The Linux Programming Interface* — Michael Kerrisk | 2 |
| *Understanding the Linux Kernel* — Bovet & Cesati | 2 |
| *Linkers & Loaders* — John R. Levine | 2 |
| *Computer Systems: A Programmer's Perspective* — Bryant & O'Hallaron | 4 |
| Intel 64 and IA-32 Software Developer Manuals | 4 |
| ARM Architecture Reference Manual | 4 |
| NVIDIA CUDA Programming Guide | 4 |
| AMD HIP Programming Guide | 4 |
| *Making Embedded Systems* — Elecia White (RTOS chapters) | 4 |
| Jeff Preshing's lock-free programming blog | 3 |
| C++ Core Guidelines (isocpp.github.io) | All |
| cppreference.com | All |
| Compiler Explorer (godbolt.org) for assembly inspection | All |
| GDB documentation + rr (reverse debugger) | 2 |
| ONNX Runtime C++ API docs | 6B |

---

## 📅 Timeline Summary

```
Phase 0  [DONE]       Feb 11           Environment setup
Phase 1  [IN PROG]    Feb 11 – May 15  C++ systems (13 wk, ~4 wk remaining)
Phase 2  [UPCOMING]   May 15 – Aug 1   Linux/OS + linker + IPC + debugging (11 wk)
Phase 3               Aug 1 – Oct 10   Concurrency + atomics + RT scheduling (10 wk)
Phase 4               Oct 10 – Jan 15  Hardware arch + GPU + RTOS basics (14 wk)
Phase 5  [NEW]        Jan 15 – Feb 15  Low-level system design (4 wk)
Phase 6               Feb 15 – Apr 25  Integration projects + practical AI/ML (10 wk)
Phase 7               Apr 25 – Jun 10  Interview intensive (6 wk)
Phase 8  [ONGOING]    Continuous       Positioning & networking

Total from today (Apr 17, 2026): ~14 months
Total from original start:       ~16 months
```
