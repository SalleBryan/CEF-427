# Mini OS Simulator (C)

This project is a **user-space mini OS simulator** that runs on Linux systems. It models essential OS subsystems in C:

- **Kernel boot/init**
- **CLI and application interface**
- **CPU scheduling (round-robin)**
- **File creation (in-memory FS)**
- **Memory management (fixed-size pool)**
- **Process & thread management**

> ⚠️ This is a *simulation*, not a real kernel or bootable OS. It is designed to be a learning aid and runs like a normal Linux program.

---

## 📦 Build & Run

### Prerequisites
- **Linux**
- GCC / Clang
- Make

### Build
```bash
make
```

### Run
```bash
./mini_os
```

---

## 🧠 Core Components

### 1. Kernel
The kernel boots, initializes subsystems, and starts the command-line interface. It coordinates process creation, memory allocation, and scheduling.

### 2. CLI & Application Interface
The CLI accepts commands to create processes, run built-in applications, manage files, and inspect system state. Built-in apps are registered through a simple app table.

### 3. CPU Scheduling
A round-robin scheduler is simulated. Each ready process gets a time slice and is moved back to the end of the queue.

### 4. File System (In-Memory)
The file system supports:
- `touch <name>` → create a file
- `ls` → list created files

No disk is used; files exist only in RAM for the session.

### 5. Memory Manager
The memory manager uses a fixed-size pool divided into equal blocks. Processes request blocks, and the allocator grants or fails based on availability.

### 6. Process & Thread Management
Processes contain threads. Each process tracks:
- PID
- State (READY, RUNNING, WAITING, TERMINATED)
- Threads

---

## 🧪 CLI Commands

| Command | Description |
|--------|-------------|
| `help` | Show available commands |
| `ps` | List processes |
| `create <name>` | Create a new process |
| `run <app>` | Run a built-in app (echo, calc, sleep) |
| `schedule` | Run the round-robin scheduler for one cycle |
| `mem` | Show memory usage |
| `alloc <pid> <blocks>` | Allocate memory blocks to a process |
| `free <pid>` | Free memory of a process |
| `touch <file>` | Create a file |
| `ls` | List files |
| `exit` | Exit simulator |

---

## 🧩 Built-in Applications

- `echo` → prints user input
- `calc` → adds two integers
- `sleep` → simulates sleeping for N ticks

---

## 📁 Directory Structure

```
.
├── include/          # headers
├── src/              # implementation
├── mini_os.c         # entry point
├── Makefile
└── README.md
```

---

## ✨ Example Session

```bash
$ ./mini_os
mini-os> create shell
mini-os> run echo
Enter text: hello
App output: hello
mini-os> touch notes.txt
mini-os> ls
notes.txt
mini-os> schedule
[Scheduler] running PID 1 for 1 tick
```

---

## 🔧 Notes
- This simulator is intentionally simple and educational.
- It is safe to extend with real IPC, paging, or device drivers.

---

## 📝 License
MIT (for learning and educational use)
