import sys, platform
import ctypes, ctypes.util

path_libc = ctypes.util.find_library("c")

try:
    libc = ctypes.CDLL(path_libc)
except OSError:
    print("Unable to load the system C library")
    sys.exit()
print(f'Succesfully loaded the system C library from "{path_libc}"')

libc.printf(b"Hello World")