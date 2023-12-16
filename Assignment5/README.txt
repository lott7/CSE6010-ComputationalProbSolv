README.txt
CSE 6010 - Assignment 5
Bellman-Ford with OpenMP

---

Description:
In this assignment, you will implement the Bellman-Ford algorithm for single-source shortest paths in graphs, as discussed in class. Unlike Dijkstra's algorithm, Bellman-Ford offers the advantage of parallelization. Your task is to write a C program with OpenMP directives to calculate shortest paths in a directed graph using a parallelized version of the Bellman-Ford algorithm. The algorithm updates shortest-path estimates iteratively, with each iteration considering whether each edge can improve the estimates. Different threads handle different edges, making use of parallelism. It's important to note that the number of iterations required may vary across different runs due to the asynchronous nature of the threads.

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
	$ ./bellmanford <string> <integer> <optional_integer>
	$ ./bellmanford graph500-100K.txt 4 466

The program will then return you the shortest number between the source_vertex and the destination_vertex.
