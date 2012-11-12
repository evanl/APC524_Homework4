#
# Plots the output file as a contour map. 
# set output 'contours.png'
set dgrid3d 100,100
set title 'Heat Equation'
set key outside
set xlabel "X axis"
set ylabel "Y axis"
set zlabel "Temperature" offset 1, 0
set pm3d map
splot 'output.dat'
