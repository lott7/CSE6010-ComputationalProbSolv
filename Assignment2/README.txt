README.txt
CSE 6010 - Assignment 2
Software Modules

---

Description:
This assignment consists of writing a program to implement a program module for a priority queue (PQ) of flight information using a singly-linked-list data structure. The PQ code 
should be structured as if it were part of a software library to be used with other programs written by someone else. You should assume that the items to be stored in the PQ are 
structures that contain information about a given flight: specifically, the airline, flight number, and departure time.


Compiler and Operating System Information:
- Compiler: 5.15.90.1-microsoft-standard-WSL2 #1 SMP Fri Jan 27 02:56:13 UTC 2023 x86_64 x86_64 x86_64 GNU/Linux
- Operating System: Microsoft Windows 11 Home / Ubuntu 22.04.2 LTS
- Debugging Software: Valgrind 3.18.1

Instructions to Compile and Run the C Program:

1. Ensure you have a C compiler installed on your system. If not, you can install one appropriate for your operating system.

2. Open a terminal/command prompt and navigate to the directory containing the source code files.

3. Use the provided Makefile to compile the C program. Run the following command:
	$ make

This will use the Makefile to compile the program and create an executable.

4. Once the compilation is successful, run the executable using the following command:
	$ ./pq

The program will then return you several test case examples.
