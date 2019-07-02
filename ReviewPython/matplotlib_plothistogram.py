import matplotlib.pyplot as plt
from read_plot import read_plot
[x,y] = read_plot("histogram.dat")
plt.plot(x,y)
plt.show()
