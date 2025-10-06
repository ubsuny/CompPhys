# Start from the latest Ubuntu image
FROM ubuntu:latest

# Set environment variables to avoid user prompts during installation
ENV DEBIAN_FRONTEND=noninteractive

# Install system dependencies and Python 3.12
RUN apt-get update && apt-get install -y --no-install-recommends \
    wget \
    less \
    nano \
    g++ \
    libtool \
    rsync \
    make \
    x11-apps \
    tzdata \
    python3.12 \
    python3.12-dev \
    python3-numpy \
    python3-pip \
    python3.12-tk \
    python3.12-full \
    swig \
    ffmpeg \
    gosu \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Create a directory for the Python virtual environment
WORKDIR /opt/venv

# Upgrade pip and install virtualenv
RUN python3 -m venv /opt/venv \
    && /opt/venv/bin/pip install --no-cache-dir \
    matplotlib \
    scipy \
    numpy \
    scikit-learn \
    keras \
    tensorflow \
    ipykernel \
    ipython \
    jupyter \
    metakernel \
    zmq \
    notebook \
    pytest \
    nbval \
    pandas \
    pylint \
    pycodestyle \
    pycodestyle_magic \
    flake8 \
    Pillow \
    openpyxl \
    ipympl \
    qiskit[visualization] \
    qiskit-ibm-runtime
    numba

# Set the virtual environment as the default Python environment
ENV PATH="/opt/venv/bin:$PATH"

# Create a non-root user and set permissions
RUN useradd -ms /bin/bash compphys && \
    chown -R compphys:compphys /opt/venv  

# Entrypoints: entrypoint_wfix.sh adds the user to a specified group to solve permissions problems
COPY entrypoint.sh /usr/local/bin/entrypoint.sh
COPY entrypoint_wfix.sh /usr/local/bin/entrypoint_wfix.sh
COPY .bash_aliases /home/compphys/.bash_aliases
RUN chmod +x /usr/local/bin/entrypoint.sh && chmod +x /usr/local/bin/entrypoint_wfix.sh && chmod +x /home/compphys/.bash_aliases
ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
