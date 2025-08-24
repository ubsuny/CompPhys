#!/usr/bin/env bash

# Usage: runDocker.sh ubsuny/compphys:latest /bin/bash
# This script provides an example `docker run` command to launch the PHY410 docker container

usage() {  
    echo "Usage: ./runDocker.sh ubsuny/compphys:latest"  
    exit 1  
} 

if [ -z "$1" ]; then
    usage
fi


DOCKERHOME=/home/compphys
LOCALDIR=${PWD} # This should be your CompPhys folder that you checked out from Github
REMOTEDIR=$DOCKERHOME/$(basename $LOCALDIR) # Location inside the container where $LOCALDIR is mounted

if [ "$(uname)" == "Darwin" ]; then
    ip=$(ifconfig en0 | grep inet | awk '$1=="inet" {print $2}')
    xhost + $ip
    DISPLAYHANDLE="${DISPLAY}"
else
    DISPLAYHANDLE="${ip}:0"
fi

DOCKERCMD="docker run \
    --rm \
    -it \
    -e DISPLAY=$DISPLAYHANDLE  \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v $LOCALDIR:$REMOTEDIR \
    -w $DOCKERHOME \
    -p 8888:8888 \
    $1 /bin/bash"
echo $DOCKERCMD 
exec $DOCKERCMD
