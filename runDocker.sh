#!/usr/bin/env bash


if [ "$(uname)" == "Darwin" ]; then
    ip=$(ifconfig en0 | grep inet | awk '$1=="inet" {print $2}')
    xhost + $ip
    docker run --rm -it -e DISPLAY=$ip:0  -v /tmp/.X11-unix:/tmp/.X11-unix -v ${PWD}:${PWD} -w ${PWD} --entrypoint "/bin/bash" -p 8888:8888 $1
else
    docker run --rm -it -e DISPLAY=$DISPLAY  -v /tmp/.X11-unix:/tmp/.X11-unix -v ${PWD}:${PWD} -w ${PWD} --entrypoint "/bin/bash" -p 8888:8888 $1
fi
