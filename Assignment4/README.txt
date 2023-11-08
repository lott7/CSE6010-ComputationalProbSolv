README.txt
CSE 6010 - Assignment 4
Collisions

---

Description:
This assignment contains a C program for simulating collisions of particles in a two-dimensional box. The simulation includes interactions between particles and collisions with the box walls. Instead of using a continuous update approach, this program employs an event-driven approach, calculating precise collision times and efficiently updating particle positions only when necessary. An example test file "particles1.txt" is provided.

---

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
	$ ./particles <string> <double>
	$ ./particles particles1.txt 100.0

The program will then return you the number of connected components.
