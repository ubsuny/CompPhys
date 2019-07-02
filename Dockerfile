FROM ubuntu:16.04


# Create a user that does not have root privileges
# Set username...
ARG username=phy410
# ... with UID 1000
ENV MY_UID 1000
# ... and home directory /results (to be mounted on the host system)
ENV HOME /results
# Create the user itself
RUN useradd --create-home --home-dir ${HOME} --uid ${MY_UID} ${username}

# Set the working directory to /app
WORKDIR /app

# Copy the current directory contents into the container at /app
ADD . /app

ENV CPT_PATH=/app/cpt
ENV PYTHONPATH=/app/cpt_python
ENV PATH=/app/cpt:$PATH
RUN ./install_software.sh

# Set the python path
ENV PYTHONPATH /app/lib/python2.7/site-packages/:/app/lib/


USER root
RUN chown -R ${MY_UID} ${HOME}
# Disallow writing to the /app directory so students do not delete their work accidentally. 
RUN chmod -R 555 /app


# Set the cwd to /results
WORKDIR ${HOME}
# Switch to our newly created user
USER ${username}


# Allow incoming connections on port 8888
EXPOSE 8888

# Sit in "results"
WORKDIR ${HOME}

# Run notebook when the container launches
CMD ["jupyter", "notebook", "--ip", "0.0.0.0"]
