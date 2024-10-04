BEGIN {FS=";"; OFS=";"}
NR%1000==1 {
    filename="data/sunspot_" NR ".csv"
}
$1 < 2000. && $1 > 1990 {
    print $1,$5>filename
    }