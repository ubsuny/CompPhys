import numpy as np

def main():

    a = np.zeros(3)
    print(a)

    b = np.zeros_like(a)
    print(b)

    c = np.ones(3)
    print(c)

    d = np.linspace(0, 10, 11)
    print(d)

    e = np.arange(10)
    print(e)

    a2 = np.zeros((3,2))
    print(a2)
    print(a2.shape)

    b2 = np.zeros_like(a2)
    print(b2)

    a3 = np.arange(12)
    print(a3)

    b3 = a3.reshape((6,2))
    print(b3)

    b4 = a3.reshape((3,4))
    print(b4)

    b5 = a3.reshape((3,2,2))
    print(b5)
    

if __name__ == "__main__":
    main()
