---
geometry:
- margin=1in
mainfont: Palatino
header-includes: 
- \usepackage[document]{ragged2e}
---

# Assignment 1 
## Technical assignment 1: data representations

PHY410: Do problems 1 and 2.

PHY 505: Do all three problems.

### Instructions
1. Accept the assignment from GitHub Classroom: [`https://classroom.github.com/a/uwfJMSPr`](https://classroom.github.com/a/uwfJMSPr). GitHub will create a forked repository for you under 
   ```
   github.com/ubsuny/compphys-assignment1-<your_username>
   ```

   - This repository is just a copy of [`github.com/ubsuny/CompPhys`](github.com/ubsuny/CompPhys), our general repository for the class. 

2. Clone the repository to your laptop and create a new folder inside for the assignment (note, replace \<your_username\> with your actual GitHub username):
   ```
   cd PHY410 # Or wherever folder you use for this class
   git clone github.com/ubsuny/compphys-assignment1-<your_username>
   cd compphys-assignment1-<your_username>/Assignment1
   # Do the assignment here
   ```

3. Do the assignment. You should put your code under the folder `Assignment1`. Follow the directions closely: each problem will specify exactly what you should name your files. Note: only PHY505 students will actually write any code for assignment 1! Only Problem 3 requires writing code, while Problems 1 and 2 are written-only.

4. Once finished, you should submit two things:
   1. Submit your code to GitHub Classroom. To do this, do the usual `git add/commit/push` and PR workflow. PHY410 students can add a dummy file, say `Assignment1/Assignment1.md`, so you can at least test out GitHub Classroom with a real commit.
      ```
      cd Assignment1
      git add <add all relevant source code files, e.g., Problem3.cpp>
      git commit -m "I hope I passed"
      git push origin main
      # Then, go to github.com and make a pull request 
      # from your fork to the main repository, 
      # ubsuny/compphys-fall2025-compphys-assignment1-CompPhys
      ```
   2. Submit your writeup, including a link to your github classroom area where your code is, on UBLearns. 

\newpage
### Problem 1
What are the "two's complement" representations for the following numbers? Use N=12 bits.

   - 10
   - 436
   - 1024
   - -13
   - -1023
   - -1024

\newpage

### Problem 2
Suppose I want to compute the following series:

$$
\begin{aligned}
f_0 &= 1 \\
f_n &= 2*f_{n-1}
\end{aligned}
$$

What is the maximum $n$ that can be stored in the following C++ data types, assuming that an int is 4 bytes, a long int is 8 bytes, and each byte stores 4 bits? 

   - int
   - long int
   -  unsigned long int

\newpage

### Problem 3 (PHY505 only)
Starting from one of the C++ programs in `CompPhys/ReviewCpp`, write a C++ program, `Problem3.cpp`, in your `CompPhys/Assignment1` folder to demonstrate Problem 2 on your computer. That is, implement the series using `int`, `long int`, and `unsigned long int` variable types, and print out the value of the variable at each step of the series. Did you see what you expect? Why or why not? Note: avoid using the `pow()` function, because it implicitly converts the input arguments to `float`s. Instead, consider using a recursive function like in `CompPhys/ReviewCpp/BasicExamples/fibo.cc`.

Your code must pass this unit test: 
```
cd Assignment1
g++ -std=c++11 Problem3.cpp -o Problem3.exe
 ./Problem3.exe
```
