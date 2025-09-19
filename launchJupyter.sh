#!/bin/bash
if [ -z $1 ]; then
	JPORT=8888
else
	JPORT="${1}"
fi
jupyter-lab --ip 0.0.0.0 --port $JPORT --no-browser
