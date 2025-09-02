# PHY410/505 docker container
Ubuntu container with some basic software for UB's Computational Physics class. Python packages are installed using virtualenv under `/opt/venv`. Also creates a non-root user, `compphys`.

To build:
```
docker buildx build --push -t username/compphys:latest --platform linux/amd64,linux/arm64 .
```

To run: see `runDocker.sh` for an example. The default entrypoint (`/usr/local/bin/entrypoint.sh`) just executes the specified command as user `compphys` (for most purposes, the command should just be `/bin/bash`, which starts an interactive bash session). 

### Fixing write permissions errors
If you encounter a write error in your bind-mounted directory, the issue is probably that your user inside the container does not have write access to the folder on the host system. To fix this, we supply a modified script, `runDocker_wfix.sh`, that does runs some permissions management commands behind the scenes. Specifically:
1. Add group write permissions to your `CompPhys` folder, using `chmod g+w CompPhys`. 
2. Launch the docker container with `./runDocker_wfix.sh ubsuny:compphys/latest`. 
Behind the scenes, the modified script checks the group that owns `CompPhys` on your host system. Inside the container, the script runs `usermod -aG <group_id> <container_username>` to add the container user to that group. 
