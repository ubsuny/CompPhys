#!/bin/bash
USERNAME=compphys
# If additional args, pass to shell. Otherwise, default to /bin/bash.
if [ -z "$@" ]; then
	ARGS="/bin/bash"
else
	ARGS=$@
fi

exec /usr/sbin/gosu $USERNAME $ARGS
