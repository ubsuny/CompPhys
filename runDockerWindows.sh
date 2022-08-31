#!/usr/bin/env bash

docker run --rm -it -v ${PWD}:/home/users/compphys/CompPhys -w /home/users/compphys --entrypoint "/bin/bash" -p 8888:8888 $1
