# This file contains examples for using the commandline to prepare research data

Retrieve data using curl:

```zsh
curl https://www.sidc.be/SILSO/INFO/sndtotcsv.php > sunspot.csv
```

## using awk to select specific subsets of the data

Print the sunspot number column (#5):
```awk
awk '{print $5}' FS=";"  sunspot.csv
```

Print only the sunspot number columns (#1,#5) for the years 1900-1999:
```awk
awk '$1 > 1900 && $1 < 2000 {print $1 $5 }' FS=";"  sunspot.csv
```

Print only the sunspot number columns (#1,#5) for the years 1900-1999 and add a column that substracts 1900 from the year:
```awk
awk '$1 > 1998 && $1 < 2000 {print $1,$5,$1-1900 }' FS=";" OFS=";"  sunspot.csv
```

or squares the sunspot number:
```awk
awk '$1 > 1998 && $1 < 2000 {print $1,$5*$5 }' FS=";" OFS=";"  sunspot.csv
```

also check out sunspot.awk for an awk script that can be called via:

```zsh
awk -f awkscript.awk  datafile
```

## using sed to manipulate the data

output only lines 3-5 of the file

```sed
sed -n '3,5p' sunspot.csv
```

output everthing but lines 3-5 of the file

```sed
sed '3,5d' sunspot.csv
```

Add a newline betwen each data row
```sed
sed G sunspot.csv
```

Replace all 19s with 18s in the file
```sed
sed s/19/18/g sunspot.csv
```

Replace all ; with tabs in the file
```sed
sed s/";"/"\t"/g sunspot.csv
```