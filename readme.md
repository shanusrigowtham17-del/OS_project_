# Zombie Process Detection and Management System

## Overview

This project was developed as part of our Operating Systems Engineering coursework to understand how zombie processes are created, detected and cleaned up in Linux.

The main idea behind this project is to practically understand what happens when a child process completes its execution but the parent process does not collect its exit status.

The entire project is implemented in C using basic operating system concepts without any external libraries.

## Problem Statement

In Linux, when a child process terminates, its termination information remains in the process table until the parent collects it. Until then, the child is known as a zombie process.

Although zombie processes do not consume CPU time, they occupy process-table entries. If too many zombie processes accumulate, the system may face difficulties in creating new processes.

Our project demonstrates this problem and shows how proper process management can resolve it.

## Features

- Creates five child processes.
- Demonstrates zombie process formation.
- Detects zombie processes automatically.
- Displays the PID of each detected zombie.
- Calculates the total number of zombies.
- Cleans up zombie processes using `waitpid()`.

## How It Works

1. The parent process creates five child processes using `fork()`.
2. Each child displays its PID and terminates using `exit()`.
3. The parent waits for two seconds without collecting the exit statuses.
4. The terminated children become zombie processes.
5. The program reads process information from `/proc/PID/stat`.
6. If the process state is `Z`, it is identified as a zombie.
7. The parent calls `waitpid()` to collect the exit statuses and complete the cleanup.

## OS Concepts Used

| Concept | Purpose |
|---|---|
| Process Management | Managing parent and child processes |
| Process Creation | Creating processes using `fork()` |
| Process Termination | Terminating processes using `exit()` |
| Process Identification | Obtaining process IDs using `getpid()` |
| Process States | Identifying zombie processes |
| Process Synchronization | Collecting child termination statuses |
| Process Control Block | Understanding retained process information |
| Process Reaping | Removing zombie entries using `waitpid()` |
| Linux Virtual Filesystem | Reading process information using `/proc` |

## Technologies Used

- Programming Language: C
- Operating System: Linux / Ubuntu
- Compiler: GCC
- Linux System Calls
- Standard C Libraries

## How to Run

Make sure GCC is installed on your Linux system.

Compile the program:

```bash
gcc zombie.c -o zombie
```

Execute the program:

```bash
./zombie
```

## Sample Output

```text
ZOMBIE PROCESS MANAGEMENT SYSTEM

Child 1: PID = 2101
Child 2: PID = 2102
Child 3: PID = 2103
Child 4: PID = 2104
Child 5: PID = 2105

Checking Zombie Processes
Zombie Found: PID 2101
Zombie Found: PID 2102
Zombie Found: PID 2103
Zombie Found: PID 2104
Zombie Found: PID 2105

Total Zombies: 5

Cleaning Zombie Processes
Cleanup Completed
```

The process IDs and execution order may vary each time the program runs.

## Limitations

Currently, the program detects and cleans up only the child processes created by itself. It cannot directly reap zombie processes belonging to other applications.

The program is designed for Linux because it uses the `/proc` filesystem for process detection.

## Future Improvements

- System-wide zombie process detection.
- Identification of parent process IDs.
- Real-time process monitoring.
- Warning messages for excessive zombie accumulation.
- Process monitoring dashboard.
- Automated diagnostic reports.

## What We Learned

Through this project, we gained a better understanding of how processes are created, executed and terminated in an operating system.

We also understood why zombie processes exist, how Linux maintains process information and why collecting child termination statuses is important.

Rather than just studying these concepts theoretically, this project helped us observe actual process behaviour in a Linux environment.

## Conclusion

This project is a simple implementation of zombie process detection and management using fundamental operating system concepts. It demonstrates how improper child process handling can lead to zombie formation and how proper use of `waitpid()` can prevent their accumulation.

---

Developed as part of our Operating Systems Engineering coursework.
