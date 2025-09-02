# PHY410/505 docker container
Ubuntu container with some basic software for UB's Computational Physics class. Python packages are installed using virtualenv under `/opt/venv`. Also creates a non-root user, `compphys`.

To build:
```
docker buildx build --push -t username/compphys:latest --platform linux/amd64,linux/arm64 .
```

To run: see `runDocker.sh` for an example. The default entrypoint (`/usr/local/bin/entrypoint.sh`) just executes the specified command as user `compphys` (for most purposes, the command should just be `/bin/bash`, which starts an interactive bash session). 

If you encounter a write permissions error in your bind-mounted directories, the issue is probably that the user or group does not match between (1) the owner of the directory on the host side and (2) the user inside the container. To fix this, we supply a modified Docker entrypoint (i.e., the script that runs when you start the Docker container) that adds the container user to the primary group of the host user. Do the following:
- On the host, add group write access to the directory. Assuming you are bind-mounting the CompPhys directory, execute `sudo chmod g+w CompPhys` .
- Start the container with the following arguments:
``` 
docker run --entrypoint "/usr/local/bin/entrypoint_uidfix.sh" (the rest of the commands) $(id -g $(whoami))
```

You could also change the group of the host directory to match the GID of the container user:
- Inside the container, run `getent group | grep compphys` to get the container user GID.
- On the host, create a new group with the GID from the first step: `sudo groupadd -g NNNN dockerusers` .
- On the host, change the group owner of the desired directory: `sudo chgrp -R dockerusers CompPhys` . 
- On the host, add group write access: `sudo chmod g+w CompPhys` .
