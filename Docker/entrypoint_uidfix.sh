#!/bin/bash
USERNAME=compphys
LOCAL_GID=$1
if [ -z $LOCAL_GID ]; then
	echo "Usage: docker run --entrypoint /usr/local/bin/entrypoint_uidfix.sh ... LOCAL_GID"
	exit 1
fi

echo "Adding user to group: $LOCAL_GID"
usermod -aG $LOCAL_GID $USERNAME

exec /usr/sbin/gosu $USERNAME /bin/bash

#/bin/bash "$@"

#useradd -u $UID -o -m $USERNAME
#groupmod -g $GID $USERNAME
#export HOME=/home/$USERNAME
#chown -R $USERNAME:$USERNAME /opt/venv

#cd $HOME
