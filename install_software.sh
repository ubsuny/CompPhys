# Ubuntu+tools, python, pip, python modules
apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y wget g++ libtool rsync make x11-apps tzdata python3-dev python3-numpy python3-pip python3-tk swig
rm -rf /var/lib/apt/lists/*
# tensorflow requires scipy==1.4.1 not newer!
pip3 install --upgrade pip && pip install --no-cache-dir matplotlib scipy==1.4.1 numpy scikit-learn keras tensorflow ipykernel ipython jupyter metakernel zmq notebook pytest nbval
