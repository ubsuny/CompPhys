# Assignment 2 
## Technical assignment 2: data representations

PHY410: Do problems 1 and 2.
PHY 505: Do all three problems.  

### Instructions
1. Accept the assignment from GitHub Classroom: https://classroom.github.com/blahblahblah. GitHub will create a forked repository for you under github.com/ubsuny/phy410-assignment2-<your_username>. 
    - Note: replace <your_username> with your actual GitHub username
    - This repository is just a copy of github.com/ubsuny/CompPhys, our general repository for the class. 
2. Clone the repository to your laptop. Inside, you'll find a folder `Assignment2`. Do all of your work inside this folder.
    ```
    cd PHY410 # Or wherever folder you use for this class
    git clone github.com/ubsuny/phy410-assignment2-<your_username>
    cd phy410-assignment2-<your_username>/Assignment2
    # Do the assignment here
    ```
3. Do the assignment. You should put your code under the folder `Assignment2`, and each problem should reside in its own folder, e.g., `Assignment2/Problem1/`, `Assignment2/Problem2/`, and `Assignment2/Problem3/`. Follow the directions closely: each problem will specify exactly what you should name your files, and how each file will be graded. 
4. Once finished, you should submit two things:
    1. Submit your code to GitHub Classroom. To do this, do the usual `git add/commit/push` and PR workflow. Specifically,
        ```
        cd Assignment2
        git add .
        git commit -m "I hope I passed"
        git push origin main
        # Then, go to github.com and make a pull request to the main repository, ubsuny/compphys-fall2025-phy410-assignment2-CompPhys
        ```
    2. Submit your writeup, including a link to your github classroom area where your code is, on UBLearns. 

\newpage

### Problem 1

(25 points) Create a program in the file `Assignment2/Problem1/Problem1.cpp` that:

- Accepts a number as a command line argument, i.e., assuming your executable is named `Problem1.exe`, you will run it like `./Problem1.exe 5`.
- Interprets that number as a `long int` with the `atol()` function (note: this function is defined in `<stdlib.h>`);
    - Your code should gracefully handle the case where no arguments are provided. I.e., it should print an error message that reminds the user of the syntax. 
- Calculates and prints the factorial of that number.
    - The factorial should be computed by a function with the following signature: `unsigned int factorial(unsigned int x);`
    - To avoid overflows, if `x` is greater than or equal to 20, the function should print a warning message and return 0.

The "unit tests," i.e., the commands that will be used to grade the assignment, are the following:
```
cd Assignment2/Problem1/
g++ Problem1.cpp -o Problem1.exe
./Problem1.exe 10 # Should return 3628800
./Problem1.exe 20 # Should print a warning message and 0
./Problem2.exe # Should print a reminder of the expected syntax
```

\newpage

### Problem 2
(25 points)
1. (15 points) Create a class template file called `LorentzVector.h` that implements a class template of a Lorentz vector (using natural units, $c = 1$) called `template<class T> LorentzVector`. The class `T` is the type of number used for the class member data, for example `float` or `double`. 
    - Create a method called `mass()` that computes the invariant mass of a Lorentz vector ($m^2=\sqrt{E^2-p_x^-p_y^2-p_z^2}$). 
    - Create a specific class of type `LorentzVector<double>`. 
    - In `Problem2.cpp`, write your `int main()` function. In your `main()` function, create two Lorentz vectors, `v1=(1,0,0,1)` and `v2=(1,0,0,-1)` and print them. 
2. (10 points) In your `LorentzVector` class, create an addition operator called `operator+` that will sum two four vectors and return the sum. Sum the vectors, `v1` and `v2` from part 1, using the same file `Problem2.cpp`. Print the sum and its invariant mass. 

The unit tests for this problem will be:
```
cd Assignment2/Problem2/
g++ Problem2.cpp -o Problem2.exe
./Problem2.exe # This should print v1, v2, and mass(v1+v2). 
```

\newpage

### Problem 3
(25 points, PHY505 students only)

- Start by copying the example at `ReviewCpp/ClassExample/ read_points_example.cc` to `Assignment2/Problem3/Problem3.cpp`, i.e., `cp ReviewCpp/ClassExample/read_points_example.cc Assignment2/Problem3/Problem3.cpp`. 
- Create a new class, `Line`, with the class declared in `Assignment2/Problem3/Line.h` and defined in `Assignment2/Problem3/Line.cc`. The class should have:
    - Protected data members `double m_;` and `double b_`, which represent the slope and intercept of the line, respectively; 
- Copy the class files for `class Point` from `ReviewCpp/ClassExample/Point.h(cc)` into your folder, i.e., `cp ReviewCpp/ClassExample/Point* Assignment2/Problem3/`. So, your `Problem3` file should contain source code files for `Line`, `Point`, and the executable in `Problem3.cpp`.
- Define two constructors for `Line`:
    - One taking two floating point numbers, the slope and the y-intercept; 
    - One taking two `Point` objects, and then calculating the slope and y-intercept based on the two points.
- Similarly, define two `set()` methods that take the same arguments as the constructors.
- Your code should handle the following special cases:
    - The slope might be infinity. In this case, set the slope to the special value `std::numeric_limits::infinity()`. 
    - The y-intercept might be undefined. In this case, set the slope to the special value `std::nan` ("not a number"). A "quick and dirty" way to do this is to set it to `sqrt(-2)`. 
- You are welcome (and encouraged!) to copy/reuse and modify any code from the examples in the repository. 

1. (15 points) In your `int main()` function, write code that reads in a text file, `lines.txt` (provided in the starter code), creates a `Line` object for each, and prints out `"y = m x + b` for each `Line`, where the actual slope and y-intercept substituted for `m` and `b`. The `lines.txt` file contains a list of (slope, intercept) pairs:
    ```
    -1,1
    1,1
    1,1
    1,1.00000000000000005
    1,2
    3,4
    1,8
    ```
2. (10 points) Write code that sorts the list of lines from part 1 in order of increasing slope, and prints them using the same format as in part 1.

The unit tests for the problem will be:
```
cd Assignment2/Problem3
g++ Line.cc Point.cc Problem3.cpp -o Problem3.exe
./Problem3 lines.txt
```