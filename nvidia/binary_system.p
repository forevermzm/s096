set xrange [-0.6:0.6]
set yrange [-0.6:0.6]
plot "logfile.txt" using 1:2 with linespoints, \
       "logfile.txt" using 4:5 with linespoints
