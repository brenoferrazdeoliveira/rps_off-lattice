N = ` sed -n "/#define N  / p" ../rps.h | cut -f5 -d" " `
L = ` sed -n "/#define L  / p" ../rps.h | cut -f5 -d" " `
VARRHO= N/(L*L)

set terminal tikz size 8.4cm, 8.4cm fontscale 0.8 fulldoc
set output "psp.tex"

set size ratio -1
set yrange [0.0:1.0]
set xrange [0.0:1.0]
set noborder
set noxtics
set noytics

set label "$1$" at graph  0.50,  0.916 center tc rgb "#ff0000"
set label "$2$" at graph -0.03, -0.030 center tc rgb "#0000ff"
set label "$3$" at graph  1.03, -0.030 center tc rgb "#ffff00" 

set style line 11 lw 2   lc rgb "#ff0000"
set style line 12 lw 0.5 lc rgb "#ff0000" dt 2

set style line 21 lw 2   lc rgb "#0000ff"
set style line 22 lw 0.5 lc rgb "#0000ff" dt 2 

set style line 31 lw 2   lc rgb "#ffff00"
set style line 32 lw 0.5 lc rgb "#ffff00" dt 2 

# x
set arrow 11 from 0.000, 0.000 to 1.000, 0.000 nohead linestyle 11
set arrow 12 from 0.950, 0.087 to 0.050, 0.087 nohead linestyle 12
set arrow 13 from 0.900, 0.173 to 0.100, 0.173 nohead linestyle 12
set arrow 14 from 0.850, 0.260 to 0.150, 0.260 nohead linestyle 12
set arrow 15 from 0.800, 0.346 to 0.200, 0.346 nohead linestyle 12
set arrow 16 from 0.750, 0.433 to 0.250, 0.433 nohead linestyle 12
set arrow 17 from 0.700, 0.520 to 0.300, 0.520 nohead linestyle 12
set arrow 18 from 0.650, 0.606 to 0.350, 0.606 nohead linestyle 12
set arrow 19 from 0.600, 0.693 to 0.400, 0.693 nohead linestyle 12
set arrow 10 from 0.550, 0.779 to 0.450, 0.779 nohead linestyle 12

# y
set arrow 21 from 1.000, 0.000 to 0.500, 0.866 nohead linestyle 21
set arrow 22 from 0.050, 0.087 to 0.100, 0.000 nohead linestyle 22
set arrow 23 from 0.100, 0.173 to 0.200, 0.000 nohead linestyle 22
set arrow 24 from 0.150, 0.260 to 0.300, 0.000 nohead linestyle 22
set arrow 25 from 0.200, 0.346 to 0.400, 0.000 nohead linestyle 22
set arrow 26 from 0.250, 0.433 to 0.500, 0.000 nohead linestyle 22
set arrow 27 from 0.300, 0.520 to 0.600, 0.000 nohead linestyle 22
set arrow 28 from 0.350, 0.606 to 0.700, 0.000 nohead linestyle 22
set arrow 29 from 0.400, 0.693 to 0.800, 0.000 nohead linestyle 22
set arrow 20 from 0.450, 0.779 to 0.900, 0.000 nohead linestyle 22

# z
set arrow 31 from 0.500, 0.867 to 0.000, 0.000 nohead linestyle 31
set arrow 32 from 0.100, 0.000 to 0.550, 0.779 nohead linestyle 32
set arrow 33 from 0.200, 0.000 to 0.600, 0.693 nohead linestyle 32
set arrow 34 from 0.300, 0.000 to 0.650, 0.606 nohead linestyle 32
set arrow 35 from 0.400, 0.000 to 0.700, 0.520 nohead linestyle 32
set arrow 36 from 0.500, 0.000 to 0.750, 0.433 nohead linestyle 32
set arrow 37 from 0.600, 0.000 to 0.800, 0.346 nohead linestyle 32
set arrow 38 from 0.700, 0.000 to 0.850, 0.260 nohead linestyle 32
set arrow 39 from 0.800, 0.000 to 0.900, 0.173 nohead linestyle 32
set arrow 30 from 0.900, 0.000 to 0.950, 0.087 nohead linestyle 32

set key at graph 0.9, 0.9 spacing 1.5 Left reverse samplen 1.0 width 2.0

plot \
"../dat/dst.dat" \
u (0.5*($1+2*$3)/($1+$2+$3)):((sqrt(3.)/2.)*($1/($1+$2+$3))) \
w l ls 1 t sprintf("$\\varrho = %.1f$", VARRHO)

unset output
