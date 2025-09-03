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

# Setup display variables
if [ "$(uname)" == "Darwin" ]; then
    ip=$(ifconfig en0 | grep inet | awk '$1=="inet" {print $2}')
    xhost + $ip
    DISPLAYHANDLE="${DISPLAY}"
else
    DISPLAYHANDLE="${ip}:0"
fi

# Ensure group permissions on CompPhys folder
if [ "$(uname)" == "Darwin" ]; then
    GRPW=$(stat -f "%p %N" . | awk '{print $1=substr($1,length($1)-2)}' | grep -c ".[2367].")
else
    GRPW=$(stat -c "%a"  . | grep -c ".[2367].")
fi
if [ $GRPW == 0 ]; then
    echo "Adding group write permissions to CompPhys folder"
    echo "chmod -R g+w ."
    chmod -R g+w .
fi
unset GRPW

DOCKERCMD="docker run \
    --entrypoint "/usr/local/bin/entrypoint_wfix.sh" \
    --rm \
    -it \
    -e DISPLAY=$DISPLAYHANDLE  \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v $LOCALDIR:$REMOTEDIR \
    -w $DOCKERHOME \
    -p 8888:8888 \
    $1 \
    $(id -g $(whoami)) /bin/bash"
echo $DOCKERCMD 
exec $DOCKERCMD
