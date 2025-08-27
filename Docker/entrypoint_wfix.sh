#!/bin/bash
USERNAME=compphys
LOCAL_GID=$1
if [ -z $LOCAL_GID ]; then
	echo "Usage: docker run --entrypoint /usr/local/bin/entrypoint_wfix.sh ... LOCAL_GID CMD"
	exit 1
fi

echo "Adding user to group: $LOCAL_GID"
usermod -aG $LOCAL_GID $USERNAME

# If additional args, pass to shell. Otherwise, default to /bin/bash.
if [ -z "${@:2}" ]; then
	ARGS="/bin/bash"
else
	ARGS=${@:2}
fi

exec /usr/sbin/gosu $USERNAME "$ARGS"

#/bin/bash "$@"

#useradd -u $UID -o -m $USERNAME
#groupmod -g $GID $USERNAME
#export HOME=/home/$USERNAME
#chown -R $USERNAME:$USERNAME /opt/venv

#cd $HOME
