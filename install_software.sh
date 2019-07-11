# Ubuntu+tools, python, pip, python modules
apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y wget g++ libtool rsync make x11-apps tzdata python3-dev python3-numpy python3-pip python3-tk swig
rm -rf /var/lib/apt/lists/*
pip3 install --upgrade pip && pip install --no-cache-dir matplotlib scipy numpy scikit-learn keras tensorflow ipykernel ipython jupyter metakernel zmq notebook


