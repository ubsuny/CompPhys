---
geometry:
- margin=1.25in
mainfont: Palatino
header-includes: 
- \usepackage[document]{ragged2e}
---

# Assignment 4
## Physics assignment 1: Fourier transforms

### Instructions
- PHY410: Do problems 1 and 2.
- PHY 505: Do all three problems.

Accept the assignment from github classroom: https://classroom.github.com/a/0p7vIeYc. You
will then get a link to your own github area.
You should submit your code through github classroom. Submit your writeup, and a link to your
github classroom area where your code is, on UBLearns.

\newpage

## Problem 1
*25 points*

Please do the problem in Jupyter in `Problem1/Problem1.ipynb`. You are free to use either python or C++.

### Problem 1a
*15 points*


Starting from the linear `chi_square_fit()` function, create a modified function that performs an exponential fit to the CO2 data by taking the logarithm of the concentration and fitting the logarithm. 

   - The `chi_square_fit()` function has been copied to the Assignment 4 folder; you can use python or C++, your choice.
   - The CO2 data file has also been copied into the Assignment 4 folder (co2_mm_mlo.txt). 

At 50,000 ppm CO2 concentration, the atmosphere will become toxic to oxygen-breathing life.
Assuming your fitting current exponential trend, on what date will the atmosphere become toxic?


### Problem 1b
*10 points*

Repeat part a, but instead of an exponential fit, use the numpy polyfit function for a
second-degree polynomial (quadratic). Now when does the atmosphere become toxic?

\newpage

## Problem 2
*25 points*

Please do the problem in Jupyter in `Problem2/Problem2.ipynb`. You are free to use either python or C++.

In this problem, we will repeat some of the in-class activities with the sunspot data set on the CO2 data set. Using some combination of waveform modification (which may include padding, windowing, taking the FFT, manipulating the waveforms, inverse FFT, and undoing the window+padding), do the following:

### Problem 2a
*15 points*

Plot the default and smoothed Fourier power spectrum of the full CO2 data. You will need to
pad the values to the nearest power of 2, so be sure to apply a window function to the padded data (your choice of function). 

### Problem 2b
*10 points*

Clean up the jitters (high frequency noise, index > 100) in the time domain by
zeroing the appropriate waveform coefficients in the frequency domain. Plot both the "raw"
and "cleaned" spectra in the time domain. (Note: this is for demonstration and educational
purposes; it is not necessarily what you would do in real life.) Show a zoomed-in plot to see (and
demonstrate) the effect, as well as the full time-domain spectrum to see any negative
consequences. 

\newpage

## Problem 3
*25 points*

PHY505 only. Please do the problem in Jupyter in `Problem3/Problem3.ipynb`. 

### Problem 3a
*10 points*

The Fourier transform is a good tool for analyzing the period variations (i.e., annual variations) of the C02 data, but not necessarily the overall rise. Subtract out the quadratic fit of the CO2 data from Problem 1 from the input data, and then plot the resulting waveform and its Fourier transform (i.e., plot both the time domain and the frequency domain of the subtracted data). Do not apply a window; instead, truncate the inputs to the highest power of 2 for which you have data (it should be 512). 

### Problem 3b
*15 points*

Using a band pass filter from 25 to 60, zero all of the components of the power spectrum except the second-largest peak of the Fourier transform. Then, take the inverse FFT and plot the results. 

