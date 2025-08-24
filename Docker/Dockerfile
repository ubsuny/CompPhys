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
    ipympl

# Set the virtual environment as the default Python environment
ENV PATH="/opt/venv/bin:$PATH"

# Create a non-root user and set permissions
RUN useradd -ms /bin/bash compphys && \
    chown -R compphys:compphys /opt/venv  

# entrypoint.sh checks UID:GID of host user and changes docker user to match
COPY entrypoint.sh /usr/local/bin/entrypoint.sh
COPY entrypoint_uidfix.sh /usr/local/bin/entrypoint_uidfix.sh
RUN chmod +x /usr/local/bin/entrypoint.sh && chmod +x /usr/local/bin/entrypoint_uidfix.sh 
ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]

