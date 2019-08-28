from numpy import genfromtxt

def read_co2(file_name = "co2_mm_mlo.txt", verbose=False):
    '''
    # from https://www.esrl.noaa.gov/gmd/ccgg/trends/
    # CO2 expressed as a mole fraction in dry air, micromol/mol, abbreviated as ppm
    #
    #  (-99.99 missing data;  -1 no data for #daily means in month)
    #
    #            decimal     average   interpolated    trend    #days
    #             date                             (season corr)
    '''

    data = genfromtxt(file_name, comments='#')

    dates = data[:,2]
    averages = data[:,4]
    if verbose:
        print (dates)
        print(averages)
    return [dates, averages]
