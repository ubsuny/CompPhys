# Start from the latest Ubuntu image
FROM ubuntu:latest

# Set environment variables to avoid user prompts during installation
ENV DEBIAN_FRONTEND=noninteractive

# Install system dependencies and Python 3.10
RUN apt-get update && apt-get install -y --no-install-recommends \
    wget \
    g++ \
    libtool \
    rsync \
    make \
    x11-apps \
    tzdata \
    python3 \
    python3-dev \
    python3-numpy \
    python3-pip \
    python3-tk \
    python3-full \
    swig \
    ffmpeg \
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

# Create a non-root user and set permissions
RUN useradd -ms /bin/bash compphys && \
    chown -R compphys:compphys /opt/venv  

USER compphys

# Set the virtual environment as the default Python environment
ENV PATH="/opt/venv/bin:$PATH"

# Default command
CMD ["bash"]
