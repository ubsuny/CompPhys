Computational Physics
======

Software for UB's Computational Physics class.

This updates the now-deprecated project of
[PHY410](https://github.com/rappoccio/PHY410). 


This software package is to demonstrate the example code in the
UB Computational Physics class, PHY 410/505 and 411/506, developed by
Prof. Richard Gonsalves (and updated by Prof. Salvatore Rappoccio).
This is now updated 
This also includes software from the following sources : 

- Matrix class (Bjarne Stroustrup, Texas A&M University)
- FFT implementations (http://rosettacode.org/wiki/Fast_Fourier_transform)
- Numerical Recipes in C (http://apps.nrbook.com/c/index.html)
-     ---> Also some translated to python
- http://pistol.googlecode.com/svn-history/r3/Pistol/ConjGrad.py
-     ---> this translates NR routine "mnbrak" to python
- Numerical Methods for Physics (Alejandro L. Garcia) (http://www.algarcia.org/nummeth/Programs2E.html)

The examples are typically provided in both python and C++ with
a few exceptions. These have been tested with :
 - Mac OS 10.8 : python 2.7.2 and GCC 4.7.3_0.
   Mac OS 10.10: python 2.7.9 and clang-700.1.81 (g++ points to this now) 
 - Windows 7 + cygwin : python 2.7.5 and GCC 4.8.1
 - Ubuntu 12.04 LTS : python 2.7.3 and GCC 4.6.3

Additional installation instructions : 
 - Mac OS >= 10.8 :
    > Install XCode from the App Store, enable command line tools (xcode-select --install)
 - Windows 7 + cygwin
    > During installation, change the "Interpreters" 
      and "Devel" installations from "Default" to "Install". 
 - Ubuntu 12.04 : 
    > Install g++ and make on the command line via:
      sudo apt-get install build-essential

The examples include several instances where matplotlib is used. 
There are also hooks to use gnuplot. Both are often commented
out. To get started with these, try these links : 


Docker:
======================

* Install Docker:  https://docs.docker.com/install/ (execute once)
* Open your Terminal application.
* Find a preferred directory somewhere and make a "results" folder:
```
mkdir results
```
* Get the code for PHY410:
```
git clone https://github.com/rappoccio/PHY410.git
cd PHY410
```
* Execute docker image (execute every time you log in):
   * With jupyter:```./runDocker.sh srappoccio/phy410:latest```
   * With terminal:```./runDocker.sh srappoccio/phy410:latest 1```
* Your homework should go into the "results" directory you already
created or it will be overwritten when the Docker image quits.
I have disabled write access to that directory, but it isn't 100%
foolproof so you will be able to shoot themselves in the foot unless
you follow directions. 



To Compile and Run
==================
**Compile the library**
```
cd PHY410
source setup.csh (or setup.sh for bash)
cd cpt
make
```

**Compile and run the executables**
```
cd $CPT_PATH/LectureXXX
make
./program_name 
```
*Example:*
```
cd $CPT_PATH/Lecture14
make
./wheatstone
```




"Advanced" topics
=================

**If you want to make new executable file called "filename.cpp", edit the Makefile:**
   - add your new exe name "filename" to the "all" target list
   - make a "rule" for your "filename" executable
   - add your new exe name "filename" to the "clean" string
Example:
```
filename: filename.cpp
	$(CC) $^  $(LIBS) -o filename
```

**If you broke something, to revert your git repository:**
```
git checkout -- . 
```

**If you want to compile *EVERYTHING* at once, go to PHY410 directory, do NOT cd to any Lecture, and type "make"**

```
cd PHY410
source setup.csh (or setup.sh for bash)
make
```


