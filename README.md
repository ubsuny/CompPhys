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


Docker:
======================

* Install Docker:  https://docs.docker.com/install/ (execute once)
* Open your Terminal application.
* Find a preferred directory somewhere and make a "results" folder:
```
mkdir results
```
* Get the code for CompPhys:
```
git clone https://github.com/rappoccio/CompPhys.git
cd CompPhys
```
* Execute docker image (execute every time you log in):
   * With jupyter:```./runDocker.sh srappoccio/compphys:latest```
   * With terminal:```./runDocker.sh srappoccio/compphys:latest 1```
* Your homework should go into the "results" directory you already
created or it will be overwritten when the Docker image quits.
I have disabled write access to that directory, but it isn't 100%
foolproof so you will be able to shoot themselves in the foot unless
you follow directions. 


