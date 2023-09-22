README.txt
CSE 6010 - Assignment 1
Solving Nonlinear Equations

---
Description:
Root-finding is a common scientific task where we seek solutions of nonlinear equations. 
Sometimes we seek solutions of multiple equations with multiple variables. In this assignment, we 
will look at an example of such a case by finding points of intersection of two ellipses given by the 
following functions: 
f(x,y) = x^2 + y^2 - 1 = 0, g(x,y) = 5x^2 + 21y^2 - 9 = 0



Compiler and Operating System Information:
- Compiler: 5.15.90.1-microsoft-standard-WSL2 #1 SMP Fri Jan 27 02:56:13 UTC 2023 x86_64 x86_64 x86_64 GNU/Linux
- Operating System: Microsoft Windows 11 Home / Ubuntu 22.04.2 LTS

Instructions to Compile and Run the C Program:

1. Ensure you have a C compiler installed on your system. If not, you can install one appropriate for your operating system.

2. Open a terminal/command prompt and navigate to the directory containing the source code files.

3. Use the provided Makefile to compile the C program. Run the following command:
	$ make

This will use the Makefile to compile the program and create an executable.

4. Once the compilation is successful, run the executable using the following command:
	$ ./solution

Then you will have to specify two user inputs, x0 and y0.
