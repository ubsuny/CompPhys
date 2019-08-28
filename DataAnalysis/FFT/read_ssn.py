from numpy import genfromtxt


def read_ssn(data_file_name='monthssn.dat', verbose=False):
    
    # data downloaded from http://www.sidc.be/DATA/yearssn.dat
    print ( ' Sunspot data from Solar Influences Data Analysis Center')


    data = genfromtxt(data_file_name,comments='#',usecols=(1,2))

    dates = data[:,0]
    ssns = data[:,1]
    if verbose:
        print (dates)
        print(ssns)
    return [dates, ssns]
