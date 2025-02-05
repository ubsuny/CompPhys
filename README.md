Computational Physics
======

Software for UB's Computational Physics class.

This updates the now-deprecated project of
[PHY410](https://github.com/rappoccio/PHY410). 


This software package is to demonstrate the example code in the
UB Computational Physics class, PHY 410/505 and 411/506, developed by
Prof. Richard Gonsalves (and updated by Prof. Salvatore Rappoccio, and Prof. Tim Thomay).
This also includes software from the following sources : 

- Matrix class (Bjarne Stroustrup, Texas A&M University)
- FFT implementations (http://rosettacode.org/wiki/Fast_Fourier_transform)
- Numerical Recipes in C (http://apps.nrbook.com/c/index.html)
-     ---> Also some translated to python
- http://pistol.googlecode.com/svn-history/r3/Pistol/ConjGrad.py
-     ---> this translates NR routine "mnbrak" to python
- Numerical Methods for Physics (Alejandro L. Garcia) (http://www.algarcia.org/nummeth/Programs2E.html)

Github Codespaces:
======================

Examples in this repository can be run inside a [GitHub codespace](https://github.com/features/codespaces) directly in your browser. For a general pupose codespace just click on the <span style="color:green">*green* Code</span> button.

For specific environments you can lauch a customized codespace (New with options ...). Currently available for:

- Machine Learning (ML)
- C++ (Cpp)
- Python
- QisKit

Docker:
======================

* Install Docker:  https://docs.docker.com/install/ (execute once)
* Open your Terminal application.
* Get the code for CompPhys: 
```
git clone https://github.com/ubsuny/CompPhys.git
chmod a+w CompPhys
cd CompPhys
```
* Execute docker image (execute every time you log in):
   * Linux/Unix/Mac: ```./runDocker.sh ubsuny/compphys:latest```
   * Windows: ```./runDockerWindows.sh ubsuny/compphys:latest```
* To run a `jupyter` notebook, when in the container:
   * ```jupyter notebook --ip 0.0.0.0 --no-browser``` 


For some reason, Windows often is removing the interactive portion from the script above, so copy and paste this into your PowerShell by hand: 

```
docker run --rm -it -v ${PWD}:/home/users/compphys/CompPhys -w /home/users/compphys --entrypoint "/bin/bash" -p 8888:8888 ubsuny/compphys:latest
```
