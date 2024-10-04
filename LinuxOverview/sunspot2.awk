BEGIN {FS=";"; OFS=";"}
$1 %10==1 {
    filename="data/sunspot_" $1 ".csv"
}
$1 < 2000. && $1 > 1900 {
    print $1,$5,log($5)>filename
    }