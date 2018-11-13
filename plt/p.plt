N = ` sed -n "/#define N  / p" ../rps.h | cut -f5 -d" " `
L = ` sed -n "/#define L  / p" ../rps.h | cut -f5 -d" " `
NF= ` sed -n "/#define NF / p" ../rps.h | cut -f4 -d" " `

set terminal png size 1000, 1000
ext="png"
unset xtics
unset ytics
unset colorbox

unset key
set xrange [0:L]
set yrange [0:L]

set style line 1 lc rgb "#ff0000" pt 7 ps 1.5
set style line 2 lc rgb "#0000ff" pt 7 ps 1.5
set style line 3 lc rgb "#ffff00" pt 7 ps 1.5

i= 1
while (i <= NF ){
	set output sprintf("p-%d.%s", i, ext)
	plot\
	     sprintf("../dat/p-1-%d.dat", i) u ($1):($2) ls 1,\
	     sprintf("../dat/p-2-%d.dat", i) u ($1):($2) ls 2,\
	     sprintf("../dat/p-3-%d.dat", i) u ($1):($2) ls 3
	i= i+ 1
}
unset output
