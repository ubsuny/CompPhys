#!/usr/bin/env bash


if [ "$(uname)" == "Darwin" ]; then
    if [ $# -eq 2 -a $2 -eq 1 ]
    then
	icommand=--"entrypoint /bin/bash"
    else
	icommand=""
    fi

    ip=$(ifconfig en0 | grep inet | awk '$1=="inet" {print $2}')
    xhost + $ip
    docker run --rm -it -e DISPLAY=$ip:0  -v /tmp/.X11-unix:/tmp/.X11-unix -v ${PWD}/../results:/results ${icommand} -p 8888:8888 $1
else

    if [ $# -eq 2 -a $2 -eq 1 ]
    then
	docker run -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v ${PWD}/../results:/results --rm -it --user $(id -u) --entrypoint "/bin/bash" -p 8888:8888 $1 
    else
	docker run -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v ${PWD}/../results:/results --rm -it --user $(id -u) --entrypoint "/usr/local/bin/jupyter" -p 8888:8888 $1 notebook --ip 0.0.0.0 --no-browser --allow-root 
    fi



fi
