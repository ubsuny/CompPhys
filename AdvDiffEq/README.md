# Using N-body starter code by Hut and Makino for N-body simulation

Full details are [here](https://www.ids.ias.edu/~piet/act/comp/algorithms/starter).

## Download, compile, execute figure 8

### Get the code:

- Linux:
```
wget https://www.ids.ias.edu/sites/ids.ias.edu/files/imported/act/comp/algorithms/starter/nbody_sh1.tar.gz
```
- Mac:
```
curl -O https://www.ids.ias.edu/sites/ids.ias.edu/files/imported/act/comp/algorithms/starter/nbody_sh1.tar.gz
```

### Unpack the code:
```
mkdir hut_makino
tar -zxvf nbody_sh1.tar.gz --directory hut_makino
``` 

### Compile:
```
cd hut_makino
g++ nbody_sh1.C -o nbody_sh1
chmod +x nbody_sh1
cd ..
```

### Execute a Figure-8:
```
./hut_makino/nbody_sh1 -o 0.01 < figure8.in > figure8.out
```

## Generate a random setup:
```
python generate_random_start.py > random.in
```

### Run random
```
./hut_makino/nbody_sh1 -o 0.01 < random.in > random.out
```

## Animate 

### Animate the Figure-8
```
python nbody_animate.py
```

### Animate the random config:
```
python nbody_animate.py random.out
```
