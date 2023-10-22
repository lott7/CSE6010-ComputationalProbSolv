README.txt
CSE 6010 - Assignment 3
Connected Components

---

Description:
The assignment involves analyzing a social network represented as a graph to study disease transmission. The graph's nodes represent people, and the edges represent relationships, categorized as frequent and occasional contacts. The task is to write a C program to calculate the number of connected components in the graph, which are sets of nodes where each node can be reached from any other within the same component. This analysis is conducted both for the entire network and for a network with only frequent contacts, providing insights into the impact of isolating occasional contacts on disease spread. Depth-First Search (DFS) is used to count the connected components in each graph. A test file called "connections_test.txt" is provided.

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
	$ ./connected <string> <integer>
	$ ./connected connections_test.txt 2

The program will then return you the number of connected components.
