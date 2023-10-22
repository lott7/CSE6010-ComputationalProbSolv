README.txt
CSE 6010 - Assignment 1
Solving Nonlinear Equations

---

Description:
Root-finding is a common scientific task where we seek solutions of nonlinear equations. Sometimes we seek solutions of multiple equations with multiple variables.
In this assignment, we will look at an example of such a case by finding points of intersection of two ellipses given by the following functions:

𝑓(𝑥, 𝑦) = 𝑥^2 + 𝑦^2 - 1 = 0,
𝑔(𝑥, 𝑦) = 5𝑥^2 + 21𝑦^2 - 9 = 0.

The first equation describes a circle centered at the origin with radius 1, and the second specifies an intersecting ellipse centered at the origin. We would expect
that there will be four solutions, one in each quadrant. We can use substitution to find the four intersection points as:

(√3/2, 1/2), (√3/2, -1/2), (-√3/2, 1/2), (-√3/2, -1/2).

There are many different ways to find a solution. For this assignment, you will use two different techniques in the same code (one after the other). Because the focus
is on getting familiar with C, the methods will be largely specified here, and your task will be to implement these methods.

Method 1: Newton’s method:
When it is possible to take derivatives of the desired function, Newton’s method often converges quickly. We will not derive Newton’s method for systems here, but
essentially we form an iterative scheme that can be written in matrix form as follows:

[x_n+1, y_n+1].T = [x_n,y_n].T - J^(-1) (x_n,y_n) * [f(x_n, y_n), g(x_n, y_n)]

Here the matrix J is formed by taking partial derivatives of the ellipse functions as follows:

J(x_n, y_n) = [2x_n  2y_n
               10x_n 42y_n]

Although the method is easiest to describe in matrix form, in practice, you should not explicitly form matrices or arrays in your code but rather just keep track of the four entries of the 2x2 matrix and the two entries of the matrix-vector product (e.g., compute x_n+1 = J_11(x_n, y_n) * f(x_n, y_n) + J_12(x_n, y_n) * g(x_n, y_n) and similarly for y_n+1). You will need to find the inverse of the matrix J as part of your iterative scheme, which can be done analytically for a 2x2 matrix M as:

M^(-1) = 1 / (m_11 * m_22 - m_12 * m_21) * [m_22  -m_12
                                             -m_21   m_11].

As you will see, when Newton’s method converges, it converges much more quickly than the fixed-point iteration approach, when it converges. Note that the method should fail if the matrix J is singular (whenever J_11*J_22 - J_12*J_21 = 0).

Method 2: Fixed-point iteration
Fixed-point iteration is another method that can be used to solve multiple equations. The basic idea is to develop a related function that can be iterated (perform operations using some numbers, then perform the same operation on the output of the previous iteration, and repeat). This type of calculation, if properly designed, can converge to the same output. For this assignment, use the following iterative functions:

x_n+1 = (1 - y_n) / 2
y_n+1 = (1 / √21) * √(9 - 5x_n^2)

It can be shown that this iterative scheme, if it converges, will converge to a solution of the desired equations. Note that because square roots are involved, you should expect to find only the intersection point with positive values. In addition, the method should fail if at any point it needs to take the square root of a negative number.

---

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
